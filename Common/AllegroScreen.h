#ifndef _ALLEGROSCREEN_H
#define _ALLEGROSCREEN_H

#include "ColorDepth.h"
#include "ObjectSize.h"

#include <allegro.h>

class AllegroSystem;

class AllegroScreen
{
private:
	friend class AllegroSystem;

	BITMAP *mBitmap;

private:
	AllegroScreen(const ObjectSize &size,
		bool fullScreen = false,
		ColorDepth colorDepth = DepthAuto);

public:
	inline BITMAP *bitmap() const { return mBitmap; }
};

#endif
