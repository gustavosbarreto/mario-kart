#include "Track.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Track::Track(int number) : mNumber(number) {
  std::stringstream mapFileName;
  mapFileName << "Data/Track" << number << ".bmp";
  mBitmap = load_bitmap(mapFileName.str().c_str(), NULL);
}

const TrackInfo Track::info() {
  TrackInfo info;

  stringstream infoFileName;
  infoFileName << "Data/Track";
  infoFileName << mNumber << ".dat";

  ifstream ifs(infoFileName.str().c_str(), ios::binary);
  ifs.read((char *)&info, sizeof(info));

  return info;
}