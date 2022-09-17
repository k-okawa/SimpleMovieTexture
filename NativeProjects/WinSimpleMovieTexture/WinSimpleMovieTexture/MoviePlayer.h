#pragma once

#include <dshow.h>
#include "qedit.h"
#include <thread>
#include <atlbase.h>

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();

	HRESULT Init(char* filePath);
private:
	std::unique_ptr<wchar_t[]> _moviePath;

	CComPtr<IGraphBuilder>  m_pGB;          // GraphBuilder
	CComPtr<IMediaControl>  m_pMC;          // Media Control
	CComPtr<IMediaPosition> m_pMP;          // Media Position
	CComPtr<IMediaEvent>    m_pME;          // Media Event
	CComPtr<IBaseFilter>    m_pRenderer;    // our custom renderer

	//! @param ïù  
	LONG m_lWidth;
	//! @param çÇÇ≥
	LONG m_lHeight;
	//! @param ÉsÉbÉ`
	LONG m_lPitch;
};

