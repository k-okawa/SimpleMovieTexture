#include "MovieTexture.h"

MovieTexture::MovieTexture(LPUNKNOWN pUnk, HRESULT* phr)
	: CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer), NAME("Texture Renderer"), pUnk, phr) {
	ASSERT(phr);
	if (phr)
		*phr = S_OK;
}

MovieTexture::~MovieTexture() {

}

HRESULT MovieTexture::CheckMediaType(const CMediaType* pmt) {
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

HRESULT MovieTexture::SetMediaType(const CMediaType* pmt) {
	VIDEOINFO* pviBmp;
	pviBmp = (VIDEOINFO*)pmt->Format();

	lVidWidth = pviBmp->bmiHeader.biWidth;
	lVidHeight = pviBmp->bmiHeader.biHeight;
	lVidPitch = (lVidWidth * 3 + 3) & ~(3);
 
	LONG bufferSize = lVidHeight * lVidWidth * 4;
	pTextureBuffer = std::make_unique<byte[]>(bufferSize); // R8G8B8A8
	memset(pTextureBuffer.get(), UCHAR_MAX, bufferSize);

	return S_OK;
}

HRESULT MovieTexture::DoRenderSample(IMediaSample* pSample) {
	BYTE* pBmpBuffer;
	BYTE* pTxtBuffer = pTextureBuffer.get();

	CheckPointer(pSample, E_POINTER);

	pSample->GetPointer(&pBmpBuffer);

	int texIndex = 0;
	int sampleIndex = 0;
	for (int h = 0; h < lVidHeight; h++) {
		for (int w = 0; w < lVidWidth; w++) {
			BYTE b = pBmpBuffer[sampleIndex++];
			BYTE g = pBmpBuffer[sampleIndex++];
			BYTE r = pBmpBuffer[sampleIndex++];
			pTextureBuffer[texIndex++] = r;
			pTextureBuffer[texIndex++] = g;
			pTextureBuffer[texIndex++] = b;
			pTextureBuffer[texIndex++] = UCHAR_MAX;
		}
	}

	return S_OK;
}