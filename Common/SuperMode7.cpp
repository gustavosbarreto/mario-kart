#include "SuperMode7.h"

#include <iostream>
#include <cmath>

namespace SuperMode7
{

// Very, very slow ;p
void DrawMode7Stretched(BITMAP *target,
	BITMAP *bitmap,
	float angle,
	float cameraX,
	float cameraY,
	Params params,
	int backgroundColor
	)
{
	int screenX, screenY;

	float distance, horizontalScale;

	int temp1 = bitmap->w - 1;
	int temp2 = bitmap->h - 1;

	float lineDX, lineDY;
	float spaceX, spaceY;

	static BITMAP *temp;
	if (!temp)
		temp = create_bitmap(SCREEN_W / 2, SCREEN_H / 2);

	floodfill(temp, 0, 0, backgroundColor);

	for (screenY = -params.horizon; screenY < temp->h; screenY++) {
		distance = (params.spaceZ * params.scaleY) / (screenY + params.horizon);
		horizontalScale = (distance / params.scaleX);
		lineDX = -sin(angle) * horizontalScale;
		lineDY = cos(angle) * horizontalScale;
		spaceX = cameraX + (distance * cos(angle)) - temp->w * lineDX;
		spaceY = cameraY + (distance * sin(angle)) - temp->w * lineDY;

		for (screenX = 0; screenX < temp->w; screenX++) {
			if ((spaceX<temp1) && (spaceY<temp2) && (spaceX>0) && (spaceY>0))
				putpixel(temp, screenX, screenY, getpixel(bitmap, spaceX, spaceY));

			spaceX += lineDX + lineDX;
			spaceY += lineDY + lineDY;
		}			
	}

	stretch_sprite(target, temp, 0, 0, SCREEN_W, SCREEN_H);
	clear(temp);
}

void DrawObject(BITMAP *target,
	BITMAP *bitmap,
	float angle,
	float objectX,
	float objectY,
	float cameraX,
	float cameraY,
	Params params)
{
	float newObjectX = objectX - cameraX;
	float newObjectY = objectY - cameraY;

	float spaceX = (newObjectX * cos(angle)) + (newObjectY * sin(angle));
	float spaceY = (-(newObjectX * sin(angle))) + (newObjectY * cos(angle));

	int screenX = target->w / 2 + ((params.scaleX / spaceX) * spaceY);
	int screenY = ((params.spaceZ * params.scaleY) / spaceX) - params.horizon;

	screenY*=2;

	int width = bitmap->w * (params.objScaleX / spaceX);
	int height = bitmap->h * (params.objScaleY / spaceX);

	stretch_sprite(target, bitmap, screenX - width / 2, screenY - height, width, height);
}

};
