#ifndef _ALLEGROKEYBOARD_H
#define _ALLEGROKEYBOARD_H

class AllegroSystem;

class AllegroKeyboard {
private:
  friend class AllegroSystem;

  AllegroKeyboard();

  void update();

public:
  bool isKeyDown(int keyValue) const;
};

#endif
