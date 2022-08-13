#include "MoviePlayer.h"
#include "project.h"

MoviePlayer::MoviePlayer() {

}

MoviePlayer::~MoviePlayer() {
	if (_pGraph != nullptr) _pGraph->Release();
	if (_pControl != nullptr) _pControl->Release();
	if (_pSampleGrabberFilter != nullptr) _pSampleGrabberFilter->Release();
	if (_pSampleGrabber != nullptr) _pSampleGrabber->Release();
	if (_pVideoWindow != nullptr) _pVideoWindow->Release();
}

void MoviePlayer::Init(char* filePath) {
	global::DebugLog("MoviePlayer::Init");
	global::DebugLog(filePath);

	//HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&_pGraph);
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Could not create the Filter Graph Manager"); return;

	//hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&_pSampleGrabberFilter);
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Could not create Sample Grabber Filter."); return;

	//hr = _pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&_pSampleGrabber);
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed getting ISampleGrabber."); return;

	//ZeroMemory(&mediaType, sizeof(mediaType));
	//mediaType.majortype = MEDIATYPE_Video;
	//mediaType.subtype = MEDIASUBTYPE_RGB24;
	//mediaType.formattype = FORMAT_VideoInfo;
	//_pSampleGrabber->SetMediaType(&mediaType);

	//hr = _pGraph->AddFilter(_pSampleGrabberFilter, L"Sample Grabber");
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed add SampleGrabberFilter."); return;

	//hr = _pGraph->QueryInterface(IID_IMediaControl, (void**)&_pControl);
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed getting IMediaControl."); return;

	//hr = _pGraph->RenderFile(global::CharPtrToLPWSTR(filePath), NULL);
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed render file."); return;

	//hr = _pControl->Run();
	//if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed play movie."); return;
}