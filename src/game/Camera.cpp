#include "Camera.h"
#include "Player.h"
#include <cmath>
#include <iostream>

Camera::Camera() {
  mMode7Params.spaceZ = 10;
  mMode7Params.scaleX = 412;
  mMode7Params.scaleY = 412;
  mMode7Params.objScaleX = 100;
  mMode7Params.objScaleY = 100;
  mMode7Params.horizon = -90;

  mPositionX = 940;
  mPositionY = 630;
  mAngle = -1.57;
}

void Camera::update(Player *player) {
  mAngle = player->angle();
  mPositionX = (player->x() + (-35 * cos(mAngle))) + cos(mAngle + 64);
  mPositionY = (player->y() + (-35 * sin(mAngle))) + sin(mAngle + 64);
}
