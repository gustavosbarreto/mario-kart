#include "Track.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Track::Track(int number) : mNumber(number) {
  std::stringstream mapFileName;
  // Prefer PNG; fallback to BMP if PNG is not available
  mapFileName << "data/Track" << number << ".png";
  mBitmap = load_bitmap(mapFileName.str().c_str(), NULL);
  if (!mBitmap) {
    std::stringstream bmpFileName;
    bmpFileName << "data/Track" << number << ".bmp";
    mBitmap = load_bitmap(bmpFileName.str().c_str(), NULL);
  }
}

const TrackInfo Track::info() {
  TrackInfo info;

  stringstream infoFileName;
  infoFileName << "data/Track";
  infoFileName << mNumber << ".dat";

  ifstream ifs(infoFileName.str().c_str(), ios::binary);
  ifs.read((char *)&info, sizeof(info));

  return info;
}