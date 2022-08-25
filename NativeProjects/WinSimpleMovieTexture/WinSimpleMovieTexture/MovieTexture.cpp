#include "MovieTexture.h"

MovieTexture::MovieTexture(LPUNKNOWN pUnk, HRESULT* phr)
	: CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer), NAME("Texture Renderer"), pUnk, phr) 
{
	ASSERT(phr);
	if (phr)
		*phr = S_OK;
}

MovieTexture::~MovieTexture()
{

}

HRESULT MovieTexture::CheckMediaType(const CMediaType* pmt)
{
	HRESULT hr = E_FAIL;
	VIDEOINFO* pvi = 0;

	CheckPointer(pmt, E_POINTER);

	if (*pmt->FormatType() != FORMAT_VideoInfo)
	{
		return E_INVALIDARG;
	}

	pvi = (VIDEOINFO*)pmt->Format();

	if (IsEqualGUID(*pmt->Type(), MEDIATYPE_Video) && IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_RGB24))
	{
		hr = S_OK;
	}

	return hr;
}

HRESULT MovieTexture::SetMediaType(const CMediaType* pmt)
{
	VIDEOINFO* pviBmp;
	pviBmp = (VIDEOINFO*)pmt->Format();

	lVidWidth = pviBmp->bmiHeader.biWidth;
	lVidHeight = pviBmp->bmiHeader.biHeight;
	lVidPitch = (lVidWidth * 3 + 3) & ~(3);

	return S_OK;
}