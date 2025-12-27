#include "Player.h"

#include <cmath>
#include <iostream>

Player::Player() {
  mBitmap = create_bitmap(32, 32);
  mSprite = load_bitmap("data/Mario.png", NULL);

  // Start with a fully transparent buffer to preserve sprite alpha
  clear(mBitmap);
  blit(mSprite, mBitmap, 0, 0, 0, 0, 32, 32);

  // Ajustar isso
  mPositionX = 913;
  mPositionY = 652;

  mAcc = 0;
  mAngle = -1.57;
  mAngleAcc = -1.57;
  mVectorLength = 0;
}

void Player::processInputEvents() {
  if (key[KEY_UP])
    mAcc += 0.03;
  else
    mAcc -= 0.03;

  if (key[KEY_DOWN])
    mAcc -= 0.2;
  else if (key[KEY_LEFT])
    mAngleAcc -= (6 - mAcc) / 100;

  if (key[KEY_RIGHT])
    mAngleAcc += (6 - mAcc) / 100;

  if (key[KEY_SPACE]) {
    std::cout << "Jump!" << std::endl;
    load_sound("data/jump.wav");
  }
}

void Player::update() {
  if (mAcc > 4.0)
    mAcc = 4.0;
  if (mAcc < 0)
    mAcc = 0;

  float delta = mAngle - mAngleAcc;

  /*if (delta > 0)
          mBitmap = load_bitmap("mario15.bmp", NULL);
  else if (delta < 0)
          mBitmap = load_bitmap("mario3.bmp", NULL);
  else if (delta == 0)
          mBitmap = load_bitmap("mario1.bmp", NULL);*/

  mPositionX += mAcc * cos(mAngle);
  mPositionY += mAcc * sin(mAngle);

  if (mAngle < (M_PI * 2) * -1) {
    mAngle = delta * -1;
    mAngleAcc = delta * -1;
  } else if (mAngle > (M_PI * 2)) {
    mAngle = delta * -1;
    mAngleAcc = delta * -1;
  } else {
    mAngle = mAngleAcc;
  }
}

void Player::updateBmp(int step) {
  blit(mSprite, mBitmap, step * 32, 0, 0, 0, 32, 32);
}
