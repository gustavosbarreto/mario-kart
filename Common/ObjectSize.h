#ifndef _OBJECTSIZE_H
#define _OBJECTSIZE_H

class ObjectSize
{
private:
	int mWidth;
	int mHeight;

public:
	ObjectSize(int width, int height);

	inline int width() const { return mWidth; }
	inline void setWidth(int width) { mWidth = width; }

	inline int height() const { return mHeight; }
	inline void setHeight(int height) { mHeight = height; }
};

#endif
