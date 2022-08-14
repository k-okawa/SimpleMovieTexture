#include "MoviePlayer.h"
#include "project.h"

MoviePlayer::MoviePlayer() {

}

MoviePlayer::~MoviePlayer() {
	if (_thread.joinable()) {
		_thread.join();
	}

	if (_pBuffer != nullptr) free(_pBuffer);
	if (_pGraph != nullptr) _pGraph->Release();
	if (_pControl != nullptr) _pControl->Release();
	if (_pSampleGrabberFilter != nullptr) _pSampleGrabberFilter->Release();
	if (_pSampleGrabber != nullptr) _pSampleGrabber->Release();
	if (_pVideoWindow != nullptr) _pVideoWindow->Release();
	if (_pEvent != nullptr) _pEvent->Release();
}

void MoviePlayer::Init(char* filePath) {
	_moviePath.reset(global::CharPtrToLPWSTR(filePath));
	_thread = std::thread([this] {
		HRESULT hr = CoInitialize(NULL);

		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed CoInitialize"); return; }

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&_pGraph);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Could not create the Filter Graph Manager"); return; }

		hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&_pSampleGrabberFilter);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Could not create Sample Grabber Filter."); return; }

		hr = _pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&_pSampleGrabber);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed getting ISampleGrabber."); return; }

		ZeroMemory(&_mediaType, sizeof(_mediaType));
		_mediaType.majortype = MEDIATYPE_Video;
		_mediaType.subtype = MEDIASUBTYPE_RGB24;
		_mediaType.formattype = FORMAT_VideoInfo;
		_pSampleGrabber->SetMediaType(&_mediaType);

		hr = _pGraph->AddFilter(_pSampleGrabberFilter, L"Sample Grabber");
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed add SampleGrabberFilter."); return; }

		hr = _pGraph->QueryInterface(IID_IMediaControl, (void**)&_pControl);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed getting IMediaControl."); return; }

		hr = _pGraph->QueryInterface(IID_IMediaEvent, (void**)&_pEvent);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed getting MediaEvent."); return; }

		hr = _pGraph->RenderFile(_moviePath.get(), NULL);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed render file."); return; }

		// Window
		hr = _pGraph->QueryInterface(IID_IVideoWindow, (void**)&_pVideoWindow);
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed getting IVideoWindow."); return; }
		_pVideoWindow->put_AutoShow(OAFALSE);

		_pSampleGrabber->GetConnectedMediaType(&_mediaType);
		VIDEOINFOHEADER* pVideoInfoHeader = (VIDEOINFOHEADER*)_mediaType.pbFormat;

		_pSampleGrabber->SetBufferSamples(TRUE);

		hr = _pControl->Run();
		if (FAILED(hr)) { global::DebugLogError("SimpleMovieTexture - Failed play movie."); return; }

		long nBufferSize = _mediaType.lSampleSize;
		_pBuffer = (long*)malloc(nBufferSize);

		LONG lEventCode;
		LONG_PTR lParam1, lParam2;
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			_pEvent->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
			if (lEventCode == EC_COMPLETE) {
				break;
			}
			_pSampleGrabber->GetCurrentBuffer(&nBufferSize, _pBuffer);
		}

		free(_pBuffer);
		_pGraph->Release();
		_pControl->Release();
		_pSampleGrabberFilter->Release();
		_pSampleGrabber->Release();
		_pVideoWindow->Release();
		_pEvent->Release();

		CoUninitialize();
	});
}