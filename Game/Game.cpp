#include "Game.h"
#include "AllegroScreen.h"
#include "AllegroSystem.h"
#include "Camera.h"
#include "Opponent.h"
#include "Player.h"
#include "SuperMode7.h"
#include "Track.h"

#include <allegro.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game() : mQuit(false) {
  mCurrentTrack = new Track(1);
  mCamera = new Camera();
  mPlayer = new Player();

  TrackInfo info = mCurrentTrack->info();

  mOpponents[0] = new Opponent(Opponent::Luigi);
  mOpponents[0]->setX(913);
  mOpponents[0]->setY(604);

  mOpponents[1] = new Opponent(Opponent::Peach);
  mOpponents[1]->setX(943);
  mOpponents[1]->setY(627);
}

Game::~Game() {}

void Game::processInputEvents() {
  if (key[KEY_ESC])
    mQuit = true;

  mPlayer->processInputEvents();

  /*   if (key[KEY_UP]) {
         mCamera->setY(mCamera->y()+sin(mCamera->angle())*2);
         mCamera->setX(mCamera->x()+cos(mCamera->angle())*2);
     }
     if (key[KEY_DOWN]) {
         mCamera->setY(mCamera->y()-sin(mCamera->angle())*2);
         mCamera->setX(mCamera->x()-cos(mCamera->angle())*2);
     }

     if (key[KEY_LEFT])
         mCamera->setAngle(mCamera->angle() - 0.1);

     if (key[KEY_RIGHT])
         mCamera->setAngle(mCamera->angle() + 0.1);*/
}

void Game::update() {
  mPlayer->update();
  mCamera->update(mPlayer);
  mPlayer->updateBmp(mCamera->angle());

  for (int i = 0; i < (sizeof(mOpponents) / sizeof(*mOpponents)); i++)
    mOpponents[i]->update();
}

void Game::render() {
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
                "Player X     = %f", mPlayer->x());
  textprintf_ex(buffer, font, 10, 40, makecol(0, 0, 255), -1,
                "Player Y     = %f", mPlayer->y());
  textprintf_ex(buffer, font, 10, 50, makecol(0, 0, 255), -1,
                "Camera Angle = %f", mCamera->angle());
  textprintf_ex(buffer, font, 10, 60, makecol(0, 0, 255), -1,
                "Player Angle = %f", mPlayer->angle());
  textprintf_ex(buffer, font, 10, 70, makecol(0, 0, 255), -1,
                "FPS          = %i", AllegroSystem::LastFps);

  // Renderiza o jogador
  SuperMode7::DrawObject(buffer, mPlayer->bitmap(), mCamera->angle(),
                         mPlayer->x(), mPlayer->y(), mCamera->x(), mCamera->y(),
                         mCamera->mode7Params());

  for (int i = 0; i < (sizeof(mOpponents) / sizeof(*mOpponents)); i++) {
    Opponent *opponent = mOpponents[i];

    SuperMode7::DrawObject(buffer, opponent->bitmap(), mCamera->angle(),
                           (mPlayer->x() + opponent->x()) - mCamera->x(),
                           (mPlayer->y() + opponent->y()) - mCamera->y(),
                           opponent->x() - (opponent->x() - mPlayer->x()),
                           opponent->y() - (opponent->y() - mPlayer->y()),
                           mCamera->mode7Params());
  }

  // Joga tudo na tela
  blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
