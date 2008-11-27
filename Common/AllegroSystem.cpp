#include "AllegroSystem.h"
#include "AllegroScreen.h"
#include "AllegroKeyboard.h"

#include <iostream>
#include <string>
#include <allegro.h>

AllegroSystem *AllegroSystem::mInstance = 0;
volatile long AllegroSystem::SpeedCounter = 0;
volatile long AllegroSystem::TimeTicks = 0;
volatile int AllegroSystem::Fps = 0;
volatile int AllegroSystem::AvgFps = 0;
volatile int AllegroSystem::LastFps = 0;

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
	install_int_ex(AllegroSystem::IncrementSpeedCounter, BPS_TO_TIMER(30));

	LOCK_VARIABLE(AllegroSystem::TimeTicks);
	LOCK_FUNCTION(AllegroSystem::TimeTicker);
	install_int_ex(AllegroSystem::TimeTicker, BPS_TO_TIMER(30));
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
//	LastFps = Fps;
//	Fps = 0;
//	AvgFps = (AvgFps * LastFps) / 2;
}
END_OF_FUNCTION(AllegroSystem::IncrementSpeedCounter);

void AllegroSystem::TimeTicker()
{
	AllegroSystem::TimeTicks++;
}
END_OF_FUNCTION(AllegroSystem::TimeTicker);