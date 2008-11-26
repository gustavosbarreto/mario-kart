#include "AllegroSystem.h"
#include "AllegroKeyboard.h"
#include "TrackEditor.h"

#include <iostream>
#include <allegro.h>

int main(int argc, const char *argv[])
{
	AllegroSystem *allegro = AllegroSystem::Instance();
	allegro->setupScreen(ObjectSize(640, 480));
	allegro->initializeTimers();
	allegro->installKeyboard();

	TrackEditor editor;
	while (!editor.quit()) {
		while (AllegroSystem::SpeedCounter == 0)
			rest(100 / 60);

		while (AllegroSystem::SpeedCounter > 0) {
			long oldSpeedCounter = AllegroSystem::SpeedCounter;

			editor.processInputEvents();
			editor.update();

			AllegroSystem::SpeedCounter--;
			if (oldSpeedCounter <= AllegroSystem::SpeedCounter)
				break;
		}

		editor.render();
	}

	return 0;
}
END_OF_MAIN();
