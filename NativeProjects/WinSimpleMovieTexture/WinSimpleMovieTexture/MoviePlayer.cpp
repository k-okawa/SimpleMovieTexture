#include "MoviePlayer.h"
#include "project.h"

MoviePlayer::MoviePlayer(char* filePath) {
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&_pGraph);
	if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Could not create the Filter Graph Manager");

	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&_pSampleGrabberFilter);
	if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Could not create Sample Grabber Filter.");

	hr = _pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&_pSampleGrabber);
	if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed getting ISampleGrabber.");

	ZeroMemory(&mediaType, sizeof(mediaType));
	mediaType.majortype = MEDIATYPE_Video;
	mediaType.subtype = MEDIASUBTYPE_RGB24;
	mediaType.formattype = FORMAT_VideoInfo;
	_pSampleGrabber->SetMediaType(&mediaType);

	hr = _pGraph->AddFilter(_pSampleGrabberFilter, L"Sample Grabber");
	if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed add SampleGrabberFilter.");

	hr = _pGraph->QueryInterface(IID_IMediaControl, (void**)&_pControl);
	if (FAILED(hr)) global::DebugLogError("SimpleMovieTexture - Failed getting IMediaControl.");

	hr = _pGraph->RenderFile(L"", NULL);
}

MoviePlayer::~MoviePlayer() {
	if (_pGraph != nullptr) _pGraph->Release();
	if (_pControl != nullptr) _pControl->Release();
	if (_pSampleGrabberFilter != nullptr) _pSampleGrabberFilter->Release();
	if (_pSampleGrabber != nullptr) _pSampleGrabber->Release();
	if (_pVideoWindow != nullptr) _pVideoWindow->Release();
}