#include "Opponent.h"

#include <iostream>

Opponent::Opponent(Character character) : mCharacter(character) {
  mPositionX = 900;
  mPositionY = 520;

  mBitmap = create_bitmap(32, 32);

  switch (mCharacter) {
  case Luigi:
    mSprite = load_bitmap("Data/Luigi.png", NULL);
    break;
  case Peach:
    mSprite = load_bitmap("Data/Peach.png", NULL);
    break;
  case Mario:
    mSprite = load_bitmap("Data/Mario.png", NULL);
    break;
  }

  // Transparent background to preserve sprite alpha
  clear(mBitmap);
  blit(mSprite, mBitmap, 0, 0, 0, 0, 32, 32);
}

void Opponent::update() {
  // std::cout << "update" << std::endl;
  // mPositionY -= 0.4;
  // mPositionX -= 0.2;
}

void Opponent::loadBitmap(const std::string &fileName) {
  mBitmap = load_bitmap(fileName.c_str(), NULL);
}

void Opponent::updateBmp(int step) {
  blit(mSprite, mBitmap, step * 32, 0, 0, 0, 32, 32);
}
