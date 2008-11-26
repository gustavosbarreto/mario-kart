#include "AllegroScreen.h"

#include <iostream>
#include <string>
#include <allegro.h>

AllegroScreen::AllegroScreen(const ObjectSize &size, bool fullScreen, ColorDepth colorDepth)
{	
	int bpp = colorDepth;

	if (colorDepth == DepthAuto)
		if ((bpp = desktop_color_depth()) == 0)
			bpp = 16;

	set_color_depth(bpp);

	if (set_gfx_mode((fullScreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED),
		size.width(), size.height(), 0, 0))
		throw std::string("Não foi possível definir a profundidade de cor");

	mBitmap = create_bitmap(SCREEN_W, SCREEN_H);
}
