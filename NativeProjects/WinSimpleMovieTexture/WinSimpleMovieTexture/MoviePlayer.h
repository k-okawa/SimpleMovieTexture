#pragma once

#include <dshow.h>
#include "qedit.h"
#include <thread>
#include <atlbase.h>
#include <functional>
#include "MovieTexture.h"

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();


	HRESULT Init(char* filePath);
	BYTE* GetMovieBuffer() {
		return m_pRenderer->GetTextureBuffer();
	}
private:
	void CleanupDShow();

	std::unique_ptr<wchar_t[]> _moviePath;

	CComPtr<IGraphBuilder>  m_pGB;          // GraphBuilder
	CComPtr<IMediaControl>  m_pMC;          // Media Control
	CComPtr<IMediaPosition> m_pMP;          // Media Position
	CComPtr<IMediaEvent>    m_pME;          // Media Event
	CComPtr<MovieTexture>    m_pRenderer;    // our custom renderer

	//! @param 幅  
	LONG m_lWidth;
	//! @param 高さ
	LONG m_lHeight;
	//! @param ピッチ
	LONG m_lPitch;
};

