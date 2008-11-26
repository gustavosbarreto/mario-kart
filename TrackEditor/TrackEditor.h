#ifndef _TRACKEDITOR_H
#define _TRACKEDITOR_H

class Track;
class Camera;

class TrackEditor
{
private:
	bool mQuit;

	Track *mCurrentTrack;
	Camera *mCamera;

public:
	TrackEditor();
	~TrackEditor();

	void processInputEvents();
	void update();
	void render();

	inline bool quit() const { return mQuit; }
	inline void setQuit(bool quit) { mQuit = quit; }
};

#endif
