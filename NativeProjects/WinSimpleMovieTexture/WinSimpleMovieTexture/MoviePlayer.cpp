#include "MoviePlayer.h"
#include "project.h"

MoviePlayer::MoviePlayer() 
{

}

MoviePlayer::~MoviePlayer()
{

}

void MoviePlayer::Init(char* filePath)
{
	_moviePath.reset(global::CharPtrToLPWSTR(filePath));
}