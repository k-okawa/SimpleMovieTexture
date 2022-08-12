#pragma once

#include <dshow.h>
#include "qedit.h"

class MoviePlayer {
public:
	MoviePlayer(char* filePath);
	~MoviePlayer();
private:

	AM_MEDIA_TYPE mediaType;

	IGraphBuilder* _pGraph = nullptr;
	IMediaControl* _pControl = nullptr;
	IBaseFilter* _pSampleGrabberFilter = nullptr;
	ISampleGrabber* _pSampleGrabber = nullptr;
	IVideoWindow* _pVideoWindow = nullptr;
};

