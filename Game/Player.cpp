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
		mAcc += 0.25;
	else
		mAcc -= 0.1;

	if (key[KEY_DOWN])
		mAcc -= 0.2;
	else if (key[KEY_LEFT])
		mAngle -= 0.06;

	if (key[KEY_RIGHT])
		mAngle += 0.06;
}

void Player::update()
{
	if (mAcc > 6.0)
		mAcc = 6.0;
	if (mAcc < 0)
		mAcc = 0;

	Vector finalVector;

	printf("%f %f\n", mAngle);
	mPositionX += mAcc * cos(mAngle);
	mPositionY += mAcc * sin(mAngle);
}
