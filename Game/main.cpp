#include "AllegroKeyboard.h"
#include "AllegroSystem.h"
#include "Game.h"

#include <allegro.h>
#include <iostream>

int main() {
  AllegroSystem *allegro = AllegroSystem::Instance();
  allegro->setupScreen(ObjectSize(640, 480));
  allegro->initializeTimers();
  allegro->installKeyboard();
  int OldTime = 0;
  Game game;
  while (!game.quit()) {
    while (AllegroSystem::SpeedCounter == 0)
      rest(100 / 30);

    while (AllegroSystem::SpeedCounter > 0) {
      long oldSpeedCounter = AllegroSystem::SpeedCounter;

      game.processInputEvents();
      game.update();

      AllegroSystem::SpeedCounter--;
      if (oldSpeedCounter <= AllegroSystem::SpeedCounter)
        break;
    }

    AllegroSystem::Fps++;
    if (AllegroSystem::TimeTicks - OldTime >= 30) {
      AllegroSystem::LastFps = AllegroSystem::Fps;
      AllegroSystem::Fps = 0;
      OldTime = AllegroSystem::TimeTicks;
    }

    game.render();
  }

  return 0;
}
END_OF_MAIN();
