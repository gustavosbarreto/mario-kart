#include "Game.h"
#include "Player.h"
#include "Track.h"
#include "Camera.h"
#include "SuperMode7.h"
#include "AllegroSystem.h"
#include "AllegroScreen.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <allegro.h>

using namespace std;

Game::Game():
	mQuit(false)
{
	mCurrentTrack = new Track(1);
	mCamera = new Camera();
	mPlayer = new Player();

	TrackInfo info = mCurrentTrack->info();

//	mCamera->setX(info.startCameraX);
//	mCamera->setY(info.startCameraY);
}

Game::~Game()
{
}

void Game::processInputEvents()
{
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

void Game::update()
{
	mPlayer->update();
	mCamera->update(mPlayer);
	mPlayer->updateBmp(mCamera->angle());
}

void Game::render()
{
	BITMAP *buffer = AllegroSystem::Instance()->screen()->bitmap();

	// Renderiza a pista
	SuperMode7::DrawMode7Stretched(buffer,
		mCurrentTrack->bitmap(),
		mCamera->angle(),
		mCamera->x(),
		mCamera->y(),
		mCamera->mode7Params(),
		makecol(175, 230, 245));

	// Debug
	textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 255), -1, "Camera X     = %f", mCamera->x());
	textprintf_ex(buffer, font, 10, 20, makecol(0, 0, 255), -1, "Camera Y     = %f", mCamera->y());
	textprintf_ex(buffer, font, 10, 30, makecol(0, 0, 255), -1, "Camera Angle = %f", mCamera->angle());
	textprintf_ex(buffer, font, 10, 40, makecol(0, 0, 255), -1, "FPS          = %i", AllegroSystem::LastFps);

	// Renderiza o jogador
	SuperMode7::DrawObject(buffer,
		mPlayer->bitmap(),
		mCamera->angle(),
		mPlayer->x(),
		mPlayer->y(),
		mCamera->x(),
		mCamera->y(),
		mCamera->mode7Params());

	// Joga tudo na tela
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
