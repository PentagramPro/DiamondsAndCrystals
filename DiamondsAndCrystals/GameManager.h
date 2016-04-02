#pragma once

#include "ExplainedException.h"
#include <SDL.h>
#include <SDL_image.h>

class GameManagerException : ExplainedException
{
public:
	GameManagerException(const char* what, const char* details) : ExplainedException(what, details) {}
};

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();

	void Init();
	
	bool Loop();
	const int SCREEN_WIDTH, SCREEN_HEIGHT;
private:
	void Deinit();
	
	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
};

