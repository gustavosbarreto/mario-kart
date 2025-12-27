#ifndef ALLEGRO_COMPAT_H
#define ALLEGRO_COMPAT_H

/*
 * Allegro 4 to SDL2 Compatibility Layer
 * This header provides a minimal subset of Allegro 4 API implemented on top of SDL2
 * to allow the Mario Kart project to compile with minimal changes.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Type definitions
typedef SDL_Surface BITMAP;

// Global variables
extern BITMAP *screen;
extern TTF_Font *font;
extern const Uint8 *_sdl_keyboard_state;

// Key code mappings
#define KEY_ESC SDL_SCANCODE_ESCAPE
#define KEY_UP SDL_SCANCODE_UP
#define KEY_DOWN SDL_SCANCODE_DOWN
#define KEY_LEFT SDL_SCANCODE_LEFT
#define KEY_RIGHT SDL_SCANCODE_RIGHT

// key[] array emulation - access SDL keyboard state
#define key _sdl_keyboard_state

// Graphics mode constants
#define GFX_AUTODETECT_WINDOWED 1
#define GFX_AUTODETECT_FULLSCREEN 2

// Screen size macros
extern int SCREEN_W;
extern int SCREEN_H;

// Color depth functions
#ifdef __cplusplus
extern "C" {
#endif

// Initialization functions
int allegro_init(void);
void install_timer(void);
int install_keyboard(void);

// Graphics functions
int set_color_depth(int depth);
int desktop_color_depth(void);
int set_gfx_mode(int card, int w, int h, int v_w, int v_h);

// Bitmap functions
BITMAP *create_bitmap(int width, int height);
BITMAP *load_bitmap(const char *filename, void *pal);
void destroy_bitmap(BITMAP *bitmap);

// Drawing functions
void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y,
          int dest_x, int dest_y, int width, int height);
void stretch_sprite(BITMAP *dest, BITMAP *sprite, int x, int y, int w, int h);
void putpixel(BITMAP *bmp, int x, int y, Uint32 color);
Uint32 getpixel(BITMAP *bmp, int x, int y);
void floodfill(BITMAP *bmp, int x, int y, Uint32 color);
void clear(BITMAP *bmp);

// Color functions
Uint32 makecol(int r, int g, int b);

// Text functions
void textprintf_ex(BITMAP *bmp, TTF_Font *f, int x, int y, Uint32 color,
                   int bg, const char *format, ...);

// Timing functions
void rest(int time);

// Keyboard functions
int keyboard_needs_poll(void);
int poll_keyboard(void);

// Timer functions
typedef void (*timer_callback_t)(void);
void install_int_ex(timer_callback_t callback, int speed);

// Timer speed conversion
#define BPS_TO_TIMER(x) (1000000 / (x))

// Macro stubs for Allegro threading/locking (not needed in SDL2 single-threaded context)
#define LOCK_VARIABLE(x)
#define LOCK_FUNCTION(x)
#define END_OF_FUNCTION(x)
#define END_OF_MAIN()

// Internal SDL2 state management
void _allegro_update_screen(void);
void _allegro_poll_events(void);
void _allegro_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // ALLEGRO_COMPAT_H
