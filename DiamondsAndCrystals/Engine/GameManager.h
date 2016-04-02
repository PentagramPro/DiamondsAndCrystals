#pragma once

#include "ExplainedException.h"

#include <memory>
#include <unordered_map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "SceneFactory.h"

using std::unordered_map;
using std::string;
using std::shared_ptr;

class SceneFactory;


class GameManagerException : ExplainedException
{
public:
	GameManagerException(const char* what, const char* details) : ExplainedException(what, details) {}
};

class GameManager
{
public:
	GameManager(SceneFactory& sceneFactory);
	virtual ~GameManager();

	void Init();
	
	bool Loop();
	const int SCREEN_WIDTH, SCREEN_HEIGHT;

	SDL_Texture* LoadTexture(string assetName);
	SDL_Renderer* GetRenderer();
private:
	void Deinit();

	shared_ptr<GameObject> m_sceneRoot;
	
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Uint32 m_loopEndTime;
	SceneFactory& m_sceneFactory;
	unordered_map<string, SDL_Texture*> m_textures;
};

