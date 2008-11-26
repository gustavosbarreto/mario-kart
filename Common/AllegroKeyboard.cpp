#include "AllegroKeyboard.h"

#include <iostream>
#include <allegro.h>

AllegroKeyboard::AllegroKeyboard()
{
	install_keyboard();
}

void AllegroKeyboard::update()
{
	if (keyboard_needs_poll()) {
		poll_keyboard();
	}
}

bool AllegroKeyboard::isKeyDown(int keyValue) const
{
	return key[keyValue];
}
