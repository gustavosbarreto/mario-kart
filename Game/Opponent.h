#ifndef _OPPONENT_H
#define _OPPONENT_H

#include <string>

#include <allegro.h>

class Opponent
{
public:
	enum Character
	{
		Mario,
		Luigi,
		Peach
	};

private:
	BITMAP *mSprite;
	BITMAP *mBitmap;

	float mPositionX;
	float mPositionY;

	Character mCharacter;

public:
	Opponent(Character character);

	void update();

	inline float x() const { return mPositionX; }
	inline void setX(float positionX) { mPositionX = positionX; }
	inline float y() const { return mPositionY; }
	inline void setY(float positionY) { mPositionY = positionY; }

	inline BITMAP *bitmap() const { return mBitmap; }

    void loadBitmap(const std::string &fileName);

	void updateBmp(int step);
};

#endif

