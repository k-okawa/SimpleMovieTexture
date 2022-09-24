#pragma once

#include <dshow.h>
#include "qedit.h"
#include <thread>
#include <atlbase.h>
#include <functional>
#include <d3d11.h>
#include "MovieTexture.h"

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();


	HRESULT Init(char* filePath);
	BYTE* GetMovieBuffer() {
		return m_pRenderer->GetTextureBuffer();
	}
	LONG GetWidth() {
		return m_pRenderer->lVidWidth;
	}
	LONG GetHeight() {
		return m_pRenderer->lVidHeight;
	}

	void Play() {
		m_pMC->Run();
	}

private:
	void CleanupDShow();

	std::unique_ptr<wchar_t[]> _moviePath;

	CComPtr<IGraphBuilder>  m_pGB;          // GraphBuilder
	CComPtr<IMediaControl>  m_pMC;          // Media Control
	CComPtr<IMediaPosition> m_pMP;          // Media Position
	CComPtr<IMediaEvent>    m_pME;          // Media Event
	CComPtr<MovieTexture>    m_pRenderer;    // our custom renderer

	//! @param ïù  
	LONG m_lWidth;
	//! @param çÇÇ≥
	LONG m_lHeight;
	//! @param ÉsÉbÉ`
	LONG m_lPitch;
};

