#pragma once

#include <dshow.h>
#include "qedit.h"

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();

	void Init(char* filePath);
private:

	AM_MEDIA_TYPE mediaType;

	IGraphBuilder* _pGraph = nullptr;
	IMediaControl* _pControl = nullptr;
	IBaseFilter* _pSampleGrabberFilter = nullptr;
	ISampleGrabber* _pSampleGrabber = nullptr;
	IVideoWindow* _pVideoWindow = nullptr;
	IMediaEvent* _pEvent = nullptr;
};

