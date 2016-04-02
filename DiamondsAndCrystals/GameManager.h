#pragma once

#include "ExplainedException.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"

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

	GameObject m_sceneRoot;
	
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Uint32 m_loopEndTime;
};

