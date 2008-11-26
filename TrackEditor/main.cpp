#include "AllegroSystem.h"
#include "AllegroKeyboard.h"
//#include "Game.h"

#include <iostream>
#include <allegro.h>

int main(int argc, const char *argv[])
{
	AllegroSystem *allegro = AllegroSystem::Instance();
	allegro->setupScreen(ObjectSize(640, 480));
	allegro->initializeTimers();
	allegro->installKeyboard();

/*	Game game;
	while (!game.quit()) {
		while (AllegroSystem::SpeedCounter == 0)
			rest(100 / 60);

		while (AllegroSystem::SpeedCounter > 0) {
			long oldSpeedCounter = AllegroSystem::SpeedCounter;

			game.processInputEvents();
			game.update();

			AllegroSystem::SpeedCounter--;
			if (oldSpeedCounter <= AllegroSystem::SpeedCounter)
				break;
		}

		game.render();
	}
*/
	return 0;
}
END_OF_MAIN();
