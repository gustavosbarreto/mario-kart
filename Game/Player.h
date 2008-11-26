#ifndef _PLAYER_H
#define _PLAYER_H

#include "ObjectPoint.h"

#include <Allegro/allegro.h>
#include <string>

class Player
{
private:
	std::string mName;

	BITMAP *mBitmap;

	float mPositionX;
	float mPositionY;
	float mAcc;
	float mAngle;
	float mVectorLength;

public:
	Player();

	void processInputEvents();
	void update();

	inline float x() const { return mPositionX; }
	inline void setX(float x) { mPositionX = x; }

	inline float y() const { return mPositionY; }
	inline void setY(float y) { mPositionY = y; }

	inline float angle() const { return mAngle; }

	inline BITMAP *bitmap() const { return mBitmap; }
};

#endif
