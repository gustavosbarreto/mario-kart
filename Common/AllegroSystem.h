#ifndef _ALLEGROSYSTEM_H
#define _ALLEGROSYSTEM_H

#include "ColorDepth.h"
#include "ObjectSize.h"


class AllegroScreen;
class AllegroKeyboard;

class AllegroSystem
{
private:
	AllegroScreen *mScreen;
	AllegroKeyboard *mKeyboard;
public:
	static AllegroSystem *mInstance;

private:
	AllegroSystem();

public:
	static volatile long SpeedCounter;
	static volatile long TimeTicks;
	static volatile int Fps;
	static volatile int AvgFps;
	static volatile int LastFps;

public:
	~AllegroSystem();

	static AllegroSystem *Instance();

	bool setupScreen(const ObjectSize &size,
		bool fullScreen = false,
		ColorDepth colorDepth = DepthAuto);
	AllegroKeyboard *installKeyboard();
	void initializeTimers();
	void pollEvents(); // WARNING: Isso é realmente necessário?
	void waitForTicks();

	inline AllegroScreen *screen() const { return mScreen; }

	static void IncrementSpeedCounter();
	static void TimeTicker();
};

#endif
