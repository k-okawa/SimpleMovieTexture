#pragma once

#include <dshow.h>
#include "qedit.h"
#include <thread>

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();

	void Init(char* filePath);
	long* GetCurrentBuffer() {
		return _pBuffer;
	}
private:
	std::thread _thread;

	std::unique_ptr<wchar_t[]> _moviePath;
	AM_MEDIA_TYPE _mediaType;
	long* _pBuffer = nullptr;

	IGraphBuilder* _pGraph = nullptr;
	IMediaControl* _pControl = nullptr;
	IBaseFilter* _pSampleGrabberFilter = nullptr;
	ISampleGrabber* _pSampleGrabber = nullptr;
	IVideoWindow* _pVideoWindow = nullptr;
	IMediaEvent* _pEvent = nullptr;
};

