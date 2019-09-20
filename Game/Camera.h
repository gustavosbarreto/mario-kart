#ifndef _CAMERA_H
#define _CAMERA_H

//#include "ObjectPofloat.h"
#include "SuperMode7.h"

class Game;
class Player;

class Camera {
private:
  friend class Game;

  float mAngle;
  float mPositionX;
  float mPositionY;

  SuperMode7::Params mMode7Params;

public:
  Camera();

  void update(Player *player);

  inline float x() const { return mPositionX; }
  inline void setX(float x) { mPositionX = x; }

  inline float y() const { return mPositionY; }
  inline void setY(float y) { mPositionY = y; }

  inline float angle() const { return mAngle; }
  inline void setAngle(float angle) { mAngle = angle; }

  inline SuperMode7::Params mode7Params() const { return mMode7Params; }
};

#endif
