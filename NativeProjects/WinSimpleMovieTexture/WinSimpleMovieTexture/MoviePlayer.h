#pragma once

#include <dshow.h>
#include "qedit.h"
#include <thread>

class MoviePlayer {
public:
	MoviePlayer();
	~MoviePlayer();

	void Init(char* filePath);
private:
	std::unique_ptr<wchar_t[]> _moviePath;
};

