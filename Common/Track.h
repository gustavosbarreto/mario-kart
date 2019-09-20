#ifndef _TRACK_H
#define _TRACK_H

#include <allegro.h>

struct TrackInfo {
  double startCameraX;
  double startCameraY;
  double startAngle;
};

class Track {
private:
  int mNumber;
  BITMAP *mBitmap;

public:
  Track(int number);

  const TrackInfo info();

  inline BITMAP *bitmap() const { return mBitmap; }
};

#endif
