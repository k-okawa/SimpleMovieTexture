#include "MoviePlayer.h"
#include "project.h"
#include "MovieTexture.h"

MoviePlayer::MoviePlayer() 
{
	m_pGB = NULL;
	m_pMC = NULL;
	m_pMP = NULL;
	m_pME = NULL;
	m_pRenderer = NULL;
}

MoviePlayer::~MoviePlayer()
{

}

HRESULT MoviePlayer::Init(char* filePath)
{
	_moviePath.reset(global::CharPtrToLPWSTR(filePath));

	HRESULT hr = S_OK;
	CComPtr<IBaseFilter>    pFSrc;          // Source Filter
	CComPtr<IPin>           pFSrcPinOut;    // Source Filter Output Pin
	MovieTexture* pCTR = 0;

	if (FAILED(m_pGB.CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC)))
		return E_FAIL;

	pCTR = new MovieTexture(NULL, &hr);
	if (FAILED(hr) || !pCTR)
		return E_FAIL;

	m_pRenderer = pCTR;
	if (FAILED(hr = m_pGB->AddFilter(m_pRenderer, L"TextureRenderer")))
		return hr;

	hr = m_pGB->AddSourceFilter(_moviePath.get(), L"SOURCE", &pFSrc);
	if (hr == VFW_E_NOT_FOUND) {
		return hr;
	}
	else if (FAILED(hr)) {
		return hr;
	}

	if (SUCCEEDED(hr = pFSrc->FindPin(L"Output", &pFSrcPinOut))) {
		// AVI,MPEG1,VFW
		CComPtr<IPin> pFTRPinIn;
		if (FAILED(hr = pCTR->FindPin(L"In", &pFTRPinIn))) {
			return hr;
		}

		if (FAILED(hr = m_pGB->Connect(pFSrcPinOut, pFTRPinIn))) {
			return hr;
		}
	}
	else {
		// WMV, MPEG2
		CComPtr<IBasicAudio> IAudio;
		hr = m_pGB.QueryInterface(&IAudio);
		if (FAILED(hr)) {
			return hr;
		}
		hr = IAudio->put_Volume(0);
	}

	// Get the graph's media control, event & position interfaces
	hr = m_pGB.QueryInterface(&m_pMC);
	hr = m_pGB.QueryInterface(&m_pMP);
	hr = m_pGB.QueryInterface(&m_pME);

	if (FAILED(hr = m_pMC->Run())) {
		return hr;
	}

	return S_OK;
}