/*
 * Allegro 4 to SDL2 Compatibility Layer Implementation
 */

#include "allegro.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

// Global state
static SDL_Window *_window = NULL;
static SDL_Renderer *_renderer = NULL;
static SDL_Texture *_screen_texture = NULL;
BITMAP *screen = NULL;
TTF_Font *font = NULL;
const Uint8 *_sdl_keyboard_state = NULL;
int SCREEN_W = 0;
int SCREEN_H = 0;

static int _color_depth = 32;
static bool _quit_requested = false;

// Timer callback management
struct TimerInfo {
  timer_callback_t callback;
  Uint32 interval;
  Uint32 last_tick;
};

static std::vector<TimerInfo> _timers;

// Initialize Allegro (maps to SDL_Init)
int allegro_init(void) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    return -1;
  }
  if (TTF_Init() < 0) {
    return -1;
  }
  // Initialize SDL_image for PNG support
  int img_flags = IMG_INIT_PNG;
  if ((IMG_Init(img_flags) & img_flags) != img_flags) {
    return -1;
  }
  atexit(_allegro_cleanup);
  return 0;
}

// Install timer subsystem
void install_timer(void) {
  // Timer is already initialized with SDL_INIT_TIMER
}

// Install keyboard subsystem
int install_keyboard(void) {
  _sdl_keyboard_state = SDL_GetKeyboardState(NULL);
  return 0;
}

// Set color depth
int set_color_depth(int depth) {
  _color_depth = depth;
  return 0;
}

// Get desktop color depth
int desktop_color_depth(void) {
  SDL_DisplayMode mode;
  if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
    return SDL_BITSPERPIXEL(mode.format);
  }
  return 32; // Default to 32-bit
}

// Set graphics mode
int set_gfx_mode(int card, int w, int h, int v_w, int v_h) {
  Uint32 flags = SDL_WINDOW_SHOWN;
  if (card == GFX_AUTODETECT_FULLSCREEN) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  _window = SDL_CreateWindow("Mario Kart",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              w, h, flags);
  if (!_window) {
    return -1;
  }

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  if (!_renderer) {
    SDL_DestroyWindow(_window);
    return -1;
  }

  SCREEN_W = w;
  SCREEN_H = h;

  // Create the screen surface with correct byte order for ARGB8888
  if (screen) {
    SDL_FreeSurface(screen);
  }
  
  // Use SDL_PIXELFORMAT_ARGB8888 format masks
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
  #else
    Uint32 rmask = 0x00ff0000;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x000000ff;
    Uint32 amask = 0xff000000;
  #endif
  
  screen = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
  if (!screen) {
    return -1;
  }

  // Create screen texture for rendering
  if (_screen_texture) {
    SDL_DestroyTexture(_screen_texture);
  }
  _screen_texture = SDL_CreateTexture(_renderer,
                                      SDL_PIXELFORMAT_ARGB8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);

  // Load default font
  if (!font) {
    // Try to load a common system font
    const char *font_paths[] = {
      "Data/arial.ttf",
      NULL
    };
    
    for (int i = 0; font_paths[i] != NULL; i++) {
      font = TTF_OpenFont(font_paths[i], 12);
      if (font) break;
    }
  }

  return 0;
}

// Create a bitmap
BITMAP *create_bitmap(int width, int height) {
  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
  #else
    Uint32 rmask = 0x00ff0000;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x000000ff;
    Uint32 amask = 0xff000000;
  #endif
  
  return SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
}

// Load a bitmap from file
BITMAP *load_bitmap(const char *filename, void *pal) {
  (void)pal; // Unused

  // Try SDL_image first (supports PNG and more); fallback to BMP
  SDL_Surface *loaded = IMG_Load(filename);
  if (!loaded) {
    loaded = SDL_LoadBMP(filename);
  }
  if (!loaded) {
    return NULL;
  }

  // Decide transparency method: if image has an alpha channel, use blending;
  // otherwise apply classic magenta colorkey transparency.
  const bool has_alpha = (loaded->format->Amask != 0);
  if (!has_alpha) {
    Uint32 magenta = SDL_MapRGB(loaded->format, 255, 0, 255);
    SDL_SetColorKey(loaded, SDL_TRUE, magenta);
  } else {
    SDL_SetSurfaceBlendMode(loaded, SDL_BLENDMODE_BLEND);
  }

  // Convert to a standard ARGB8888 surface while preserving alpha/colorkey
  SDL_Surface *converted = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_ARGB8888, 0);
  SDL_FreeSurface(loaded);
  if (!converted) {
    return NULL;
  }

  // Ensure blend mode is set for alpha surfaces
  if (has_alpha) {
    SDL_SetSurfaceBlendMode(converted, SDL_BLENDMODE_BLEND);
  } else {
    // Reapply colorkey on converted surface if used
    Uint32 magenta_conv = SDL_MapRGB(converted->format, 255, 0, 255);
    SDL_SetColorKey(converted, SDL_TRUE, magenta_conv);
  }

  return converted;
}

// Destroy a bitmap
void destroy_bitmap(BITMAP *bitmap) {
  if (bitmap) {
    SDL_FreeSurface(bitmap);
  }
}

// Blit one bitmap onto another
void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y,
          int dest_x, int dest_y, int width, int height) {
  if (!source || !dest) return;

  SDL_Rect src_rect = {source_x, source_y, width, height};
  SDL_Rect dst_rect = {dest_x, dest_y, width, height};

  SDL_BlitSurface(source, &src_rect, dest, &dst_rect);

  // If blitting to screen, update the display
  if (dest == screen) {
    _allegro_update_screen();
  }
}

// Stretch and blit a sprite
void stretch_sprite(BITMAP *dest, BITMAP *sprite, int x, int y, int w, int h) {
  if (!dest || !sprite) return;

  SDL_Rect src_rect = {0, 0, sprite->w, sprite->h};
  SDL_Rect dst_rect = {x, y, w, h};

  SDL_BlitScaled(sprite, &src_rect, dest, &dst_rect);
}

// Put a pixel
void putpixel(BITMAP *bmp, int x, int y, Uint32 color) {
  if (!bmp || x < 0 || y < 0 || x >= bmp->w || y >= bmp->h) return;

  SDL_LockSurface(bmp);
  Uint32 *pixels = (Uint32 *)bmp->pixels;
  pixels[y * (bmp->pitch / 4) + x] = color;
  SDL_UnlockSurface(bmp);
}

// Get a pixel
Uint32 getpixel(BITMAP *bmp, int x, int y) {
  if (!bmp || x < 0 || y < 0 || x >= bmp->w || y >= bmp->h) return 0;

  SDL_LockSurface(bmp);
  Uint32 *pixels = (Uint32 *)bmp->pixels;
  Uint32 color = pixels[y * (bmp->pitch / 4) + x];
  SDL_UnlockSurface(bmp);
  return color;
}

// Flood fill implementation
void floodfill(BITMAP *bmp, int x, int y, Uint32 color) {
  if (!bmp || x < 0 || y < 0 || x >= bmp->w || y >= bmp->h) return;

  Uint32 target_color = getpixel(bmp, x, y);
  if (target_color == color) return;

  std::queue<SDL_Point> q;
  q.push({x, y});

  SDL_LockSurface(bmp);
  Uint32 *pixels = (Uint32 *)bmp->pixels;
  int pitch = bmp->pitch / 4;

  while (!q.empty()) {
    SDL_Point p = q.front();
    q.pop();

    if (p.x < 0 || p.y < 0 || p.x >= bmp->w || p.y >= bmp->h) continue;

    Uint32 current = pixels[p.y * pitch + p.x];
    if (current != target_color) continue;

    pixels[p.y * pitch + p.x] = color;

    q.push({p.x + 1, p.y});
    q.push({p.x - 1, p.y});
    q.push({p.x, p.y + 1});
    q.push({p.x, p.y - 1});
  }

  SDL_UnlockSurface(bmp);
}

// Clear bitmap
void clear(BITMAP *bmp) {
  if (!bmp) return;
  SDL_FillRect(bmp, NULL, 0);
}

// Make color
Uint32 makecol(int r, int g, int b) {
  // Create a color matching our surface format
  if (screen) {
    return SDL_MapRGB(screen->format, r, g, b);
  }
  // Fallback to ARGB8888 format
  return (0xFF << 24) | (r << 16) | (g << 8) | b;
}

// Text printf with extended parameters
void textprintf_ex(BITMAP *bmp, TTF_Font *f, int x, int y, Uint32 color,
                   int bg, const char *format, ...) {
  if (!bmp || !f) return;

  char buffer[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  // Extract RGB from color
  Uint8 r = (color >> 16) & 0xFF;
  Uint8 g = (color >> 8) & 0xFF;
  Uint8 b = color & 0xFF;
  SDL_Color text_color = {r, g, b, 255};

  SDL_Surface *text_surface = TTF_RenderText_Solid(f, buffer, text_color);
  if (text_surface) {
    SDL_Rect dest_rect = {x, y, text_surface->w, text_surface->h};
    SDL_BlitSurface(text_surface, NULL, bmp, &dest_rect);
    SDL_FreeSurface(text_surface);
  }
}

// Rest (delay) function
void rest(int time) {
  // Poll events to keep the window responsive
  _allegro_poll_events();
  SDL_Delay(time);
}

// Keyboard polling
int keyboard_needs_poll(void) {
  return 1; // Always poll to ensure SDL events are processed
}

int poll_keyboard(void) {
  _allegro_poll_events();
  return 0;
}

// Install timer callback
void install_int_ex(timer_callback_t callback, int speed) {
  TimerInfo timer;
  timer.callback = callback;
  timer.interval = speed / 1000; // Convert microseconds to milliseconds
  timer.last_tick = SDL_GetTicks();
  _timers.push_back(timer);
}

// Update screen by copying to texture and rendering
void _allegro_update_screen(void) {
  if (!screen || !_screen_texture || !_renderer) return;

  SDL_UpdateTexture(_screen_texture, NULL, screen->pixels, screen->pitch);
  SDL_RenderClear(_renderer);
  SDL_RenderCopy(_renderer, _screen_texture, NULL, NULL);
  SDL_RenderPresent(_renderer);
}

// Poll SDL events and update timers
void _allegro_poll_events(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      _quit_requested = true;
    }
  }

  // Update keyboard state
  _sdl_keyboard_state = SDL_GetKeyboardState(NULL);

  // Process timers
  Uint32 current_ticks = SDL_GetTicks();
  for (size_t i = 0; i < _timers.size(); i++) {
    if (current_ticks - _timers[i].last_tick >= _timers[i].interval) {
      _timers[i].callback();
      _timers[i].last_tick = current_ticks;
    }
  }
}

// Cleanup
void _allegro_cleanup(void) {
  if (font) {
    TTF_CloseFont(font);
    font = NULL;
  }
  if (screen) {
    SDL_FreeSurface(screen);
    screen = NULL;
  }
  if (_screen_texture) {
    SDL_DestroyTexture(_screen_texture);
    _screen_texture = NULL;
  }
  if (_renderer) {
    SDL_DestroyRenderer(_renderer);
    _renderer = NULL;
  }
  if (_window) {
    SDL_DestroyWindow(_window);
    _window = NULL;
  }
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
