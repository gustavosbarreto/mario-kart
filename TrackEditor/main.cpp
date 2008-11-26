#include <iostream>
#include <fstream>
#include <sstream>

///a.out 1 60293120 40304640 12582912

using namespace std;

struct TrackInfo
{
	double cameraX;
	double cameraY;
	double angle;
};

int main(int argc, char *argv[])
{
	stringstream fileName;
	fileName << "Track" << argv[1] << ".dat";

	TrackInfo info;
	info.cameraX = atof(argv[2]);
	info.cameraY = atof(argv[3]);
	info.angle = atof(argv[4]);

	ofstream out(fileName.str().c_str(), ios::binary);
	out.write((char *)&info, sizeof(info));
	out.close();

	return 0;
}
