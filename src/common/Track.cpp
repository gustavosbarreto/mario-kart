#include "Track.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Track::Track(int number) : mNumber(number) {
  std::stringstream mapFileName;
  mapFileName << "data/Track" << number << ".png";
  mBitmap = load_bitmap(mapFileName.str().c_str(), NULL);

  if (!mBitmap) {
    cerr << "Unable to load bitmap: " << mapFileName.str() << endl;
  }

  // Background music for this track
  std::string musicPath = "data/Track" + std::to_string(number) + ".ogg";
  if (!load_music(musicPath.c_str())) {
    cerr << "Unable to load music: " << musicPath << endl;
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