#pragma once

namespace global {
	void DebugLog(const char* log);
	void DebugLogError(const char* log);

	LPWSTR CharPtrToLPWSTR(char* str);
}