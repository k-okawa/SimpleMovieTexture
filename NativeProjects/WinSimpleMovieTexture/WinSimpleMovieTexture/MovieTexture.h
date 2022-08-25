#pragma once

#include <streams.h>
#include <dshow.h>

class MovieTexture : CBaseVideoRenderer 
{
public:
	MovieTexture(LPUNKNOWN pUnk, HRESULT* phr);
	~MovieTexture();

	HRESULT CheckMediaType(const CMediaType* pmt);     // Format acceptable?
	HRESULT SetMediaType(const CMediaType* pmt);       // Video format notification
	HRESULT DoRenderSample(IMediaSample* pMediaSample); // New video sample
};