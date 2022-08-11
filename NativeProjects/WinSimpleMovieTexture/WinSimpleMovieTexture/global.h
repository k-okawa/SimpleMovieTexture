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
	void DebugLog(const char* log) {
		if (debugLogFunc == nullptr) {
			return;
		}
		debugLogFunc(log);
	}
}