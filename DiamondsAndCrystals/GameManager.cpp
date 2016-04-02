#include "GameManager.h"


GameManager::GameManager() : SCREEN_HEIGHT(600), SCREEN_WIDTH(755)
{
}


GameManager::~GameManager()
{
	Deinit();
}

void GameManager::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw GameManagerException("SDL_Init returned error: ", SDL_GetError());
	
	m_window = SDL_CreateWindow("Diamonds and Crystals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		throw GameManagerException("SDL_CreateWindow couldn't create window: ", SDL_GetError());
		
	m_screenSurface = SDL_GetWindowSurface(m_window);

	SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(m_window);
}

bool GameManager::Loop()
{

	return true;
}

void GameManager::Deinit()
{
	SDL_FreeSurface(m_screenSurface);
	m_screenSurface = NULL;

	SDL_DestroyWindow(m_window);
	m_window = NULL;

	SDL_Quit();
}
