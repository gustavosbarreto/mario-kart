#include "TrackEditor.h"
#include "AllegroScreen.h"
#include "AllegroSystem.h"
#include "Camera.h"
#include "SuperMode7.h"
#include "Track.h"

#include <cmath>
#include <iostream>

#include <allegro.h>

using namespace std;

TrackEditor::TrackEditor() : mQuit(false) {
  mCurrentTrack = new Track(1);
  mCamera = new Camera();
}

TrackEditor::~TrackEditor() {}

void TrackEditor::processInputEvents() {
  if (key[KEY_ESC])
    mQuit = true;

  if (key[KEY_UP]) {
    mCamera->setY(mCamera->y() + sin(mCamera->angle()) * 2);
    mCamera->setX(mCamera->x() + cos(mCamera->angle()) * 2);
  }
  if (key[KEY_DOWN]) {
    mCamera->setY(mCamera->y() - sin(mCamera->angle()) * 2);
    mCamera->setX(mCamera->x() - cos(mCamera->angle()) * 2);
  }

  if (key[KEY_LEFT])
    mCamera->setAngle(mCamera->angle() - 0.1);

  if (key[KEY_RIGHT])
    mCamera->setAngle(mCamera->angle() + 0.1);
}

void TrackEditor::update() {}

void TrackEditor::render() {
  BITMAP *buffer = AllegroSystem::Instance()->screen()->bitmap();

  // Renderiza a pista
  SuperMode7::DrawMode7Stretched(
      buffer, mCurrentTrack->bitmap(), mCamera->angle(), mCamera->x(),
      mCamera->y(), mCamera->mode7Params(), makecol(175, 230, 245));

  // Debug
  textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 255), -1,
                "Camera X     = %f", mCamera->x());
  textprintf_ex(buffer, font, 10, 20, makecol(0, 0, 255), -1,
                "Camera Y     = %f", mCamera->y());
  textprintf_ex(buffer, font, 10, 30, makecol(0, 0, 255), -1,
                "Camera Angle = %f", mCamera->angle());

  // Joga tudo na tela
  blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
