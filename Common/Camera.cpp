#include "Camera.h"

#include <iostream>
#include <cmath>

Camera::Camera()
{
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

void Camera::update(Player *player)
{
//	mAngle = player->angle();

//	xy.x = fadd(fadd(car->xy.x, fmul(customInOut, fcos(angle))), fmul(customLeftRight, fcos(angle+itofix(64))));
	
//	mPositionX = (player->x() - 100);
//	mPositionY = (player->y() - 100);
}
