#ifndef _PLAYER_H
#define _PLAYER_H

#include <allegro.h>
#include <string>

class Player {
private:
  std::string mName;

  BITMAP *mSprite;
  BITMAP *mBitmap;

  float mPositionX;
  float mPositionY;
  float mAcc;
  float mAngle;
  float mAngleAcc;
  float mVectorLength;

public:
  Player();

  void processInputEvents();
  void update();
  void updateBmp(int step);

  inline float x() const { return mPositionX; }
  inline void setX(float x) { mPositionX = x; }

  inline float y() const { return mPositionY; }
  inline void setY(float y) { mPositionY = y; }

  inline float angle() const { return mAngle; }

  inline BITMAP *bitmap() const { return mBitmap; }
};

#endif
