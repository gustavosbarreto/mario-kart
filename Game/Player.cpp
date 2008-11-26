#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player()
{
	mBitmap = load_bitmap("Toad0.bmp", NULL);

	// Ajustar isso
	mPositionX = 945;
	mPositionY = 600;

	mAcc = 0;
	mAngle = -1.57;
	mVectorLength = 0;
}


void Player::processInputEvents()
{
	if (key[KEY_UP])
		mAcc += 0.4;
	else
		mAcc -= 0.1;

	if (key[KEY_DOWN])
		mAcc -= 0.3;
	else if (key[KEY_LEFT])
		mAngle -= 0.02;

	if (key[KEY_RIGHT])
		mAngle += 0.02;
}

void Player::update()
{
	if (mAcc > 2.0)
		mAcc = 2.0;
	if (mAcc < 0)
		mAcc = 0;

	mPositionX += mAcc * cos(mAngle);
	mPositionY += mAcc * sin(mAngle);
}
