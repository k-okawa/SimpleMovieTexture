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
 
	pTextureBuffer = std::make_unique<byte[]>(lVidHeight * lVidWidth * 4); // R8G8B8A8

	return S_OK;
}

HRESULT MovieTexture::DoRenderSample(IMediaSample* pSample) {
	BYTE* pTxtBuffer = pTextureBuffer.get();
	int width = 640;
	int height = 360;
	// ê‘
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			int index = (h * height + w) * 4;
			// R
			pTxtBuffer[index + 0] = UCHAR_MAX;
			// G
			pTxtBuffer[index + 1] = 0;
			// B
			pTxtBuffer[index + 2] = 0;
			// A
			pTxtBuffer[index + 3] = UCHAR_MAX;
		}
	}
	return S_OK;
	//BYTE *pBmpBuffer;
	//BYTE* pTxtBuffer = pTextureBuffer.get();

	//BYTE* pbS = NULL;
	//DWORD* pdwS = NULL;
	//DWORD* pdwD = NULL;
	//UINT row, col, dwordWidth;

	//CheckPointer(pSample, E_POINTER);

	//pSample->GetPointer(&pBmpBuffer);

	//dwordWidth = lVidWidth;

	//// 32bit
	//for (row = 0; row < (UINT)lVidHeight; row++)
	//{
	//	pdwS = (DWORD*)pBmpBuffer;
	//	pdwD = (DWORD*)pTxtBuffer;

	//	for (col = 0; col < dwordWidth; col++)
	//	{
	//		pdwD[0] = pdwS[0] | 0xFF000000;
	//		pdwD[1] = ((pdwS[1] << 8) | 0xFF000000) | (pdwS[0] >> 24);
	//		pdwD[2] = ((pdwS[2] << 16) | 0xFF000000) | (pdwS[1] >> 16);
	//		pdwD[3] = 0xFF000000 | (pdwS[2] >> 8);
	//		pdwD += 4;
	//		pdwS += 3;
	//	}

	//	// we might have remaining (misaligned) bytes here
	//	pbS = (BYTE*)pdwS;
	//	for (col = 0; col < (UINT)lVidWidth % 4; col++)
	//	{
	//		*pdwD = 0xFF000000 |
	//			(pbS[2] << 16) |
	//			(pbS[1] << 8) |
	//			(pbS[0]);
	//		pdwD++;
	//		pbS += 3;
	//	}

	//	pBmpBuffer += lVidPitch;
	//	pTxtBuffer += lVidWidth * 4;
	//}

	//sampleCallback(pTxtBuffer);

	//return S_OK;
}