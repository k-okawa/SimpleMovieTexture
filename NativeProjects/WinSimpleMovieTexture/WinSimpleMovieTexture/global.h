#pragma once
#include <d3d11.h>
#include <thread>
#include <mutex>
#include <memory>

#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityGraphicsD3D11.h"

namespace global {
	IUnityInterfaces* unity = nullptr;

	using DebugLogFuncType = void(*)(const char*);
	DebugLogFuncType debugLogFunc = nullptr;
	DebugLogFuncType debugLogErrorFunc = nullptr;
	void DebugLog(const char* log) {
		if (debugLogFunc == nullptr) {
			return;
		}
		debugLogFunc(log);
	}

	void DebugLogError(const char* log) {
		if (debugLogErrorFunc == nullptr) {
			return;
		}
		debugLogErrorFunc(log);
	}

	LPWSTR CharPtrToLPWSTR(char* str) {
		size_t len = std::strlen(str) + 1;
		auto wText = new wchar_t[len];
		size_t ret;
		mbstowcs_s(&ret, wText, len, str, _TRUNCATE);
		return wText;
	}
}