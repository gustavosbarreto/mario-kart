#include "AllegroKeyboard.h"

#include <allegro.h>
#include <iostream>

AllegroKeyboard::AllegroKeyboard() { install_keyboard(); }

void AllegroKeyboard::update() {
  if (keyboard_needs_poll()) {
    poll_keyboard();
  }
}

bool AllegroKeyboard::isKeyDown(int keyValue) const { return key[keyValue]; }
