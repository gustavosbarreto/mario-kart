#include "AllegroSystem.h"
#include "AllegroScreen.h"
#include "AllegroKeyboard.h"

#include <iostream>
#include <string>
#include <allegro.h>

AllegroSystem *AllegroSystem::mInstance = 0;
volatile long AllegroSystem::SpeedCounter = 0;

AllegroSystem::AllegroSystem()
{
	allegro_init();
}

AllegroSystem::~AllegroSystem()
{
}

AllegroSystem *AllegroSystem::Instance()
{
	if (!mInstance)
		mInstance = new AllegroSystem();

	return mInstance;
}

bool AllegroSystem::setupScreen(const ObjectSize &size,
	bool fullScreen,
	ColorDepth colorDepth)
{
	try {
		mScreen = new AllegroScreen(size, fullScreen, colorDepth);
	} catch (std::string e) {
		std::cout << "Ocorreu uma exceção: " << e << std::endl;
		return false;
	}

	return true;
}

AllegroKeyboard *AllegroSystem::installKeyboard()
{
	return (mKeyboard = new AllegroKeyboard());
}

void AllegroSystem::initializeTimers()
{
	install_timer();

	LOCK_VARIABLE(AllegroSystem::SpeedCounter);
	LOCK_FUNCTION(AllegroSystem::IncrementSpeedCounter);
	install_int_ex(AllegroSystem::IncrementSpeedCounter, BPS_TO_TIMER(60));
}

void AllegroSystem::pollEvents()
{
	if (mKeyboard)
		mKeyboard->update();
}

void AllegroSystem::waitForTicks()
{
}

void AllegroSystem::IncrementSpeedCounter()
{
	AllegroSystem::SpeedCounter++;
}
END_OF_FUNCTION(AllegroSystem::IncrementSpeedCounter);
