#ifndef _SUPERMODE7_H
#define _SUPERMODE7_H

/*
 * Algoritmo Super Mode 7 de texture mapping criado pela NINTENDO para
 * dar impressão de um pseudo 3D apartir de um BITMAP 2D.
 */

#include <allegro.h>

namespace SuperMode7 {
struct Params {
  float spaceZ;
  int horizon;
  float scaleX, scaleY;
  float objScaleX, objScaleY;
};

void DrawMode7Stretched(BITMAP *target, BITMAP *bitmap, float angle,
                        float cameraX, float cameraY, Params params,
                        int backgroundColor);

void DrawObject(BITMAP *target, BITMAP *bitmap, float angle, float objectX,
                float objectY, float cameraX, float cameraY, Params params);
}; // namespace SuperMode7

#endif
