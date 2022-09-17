#pragma once

#include <streams.h>
#include <dshow.h>
#include <memory>

struct __declspec(uuid("{fa36726f-a7ec-4c3d-9bdf-5a00a5209b22}")) CLSID_TextureRenderer;

class MovieTexture : public CBaseVideoRenderer 
{
	std::unique_ptr<BYTE[]> pTextureBuffer;
public:
	MovieTexture(LPUNKNOWN pUnk, HRESULT* phr);
	~MovieTexture();

	HRESULT CheckMediaType(const CMediaType* pmt);     // Format acceptable?
	HRESULT SetMediaType(const CMediaType* pmt);       // Video format notification
	HRESULT DoRenderSample(IMediaSample* pSample);     // New video sample

	LONG lVidWidth;
	LONG lVidHeight;
	LONG lVidPitch;
};