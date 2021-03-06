#pragma once

#include "ExplainedException.h"

#include <memory>
#include <unordered_map>
#include <map>
#include <forward_list>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "SceneFactory.h"
#include "Constants.h"

using std::unordered_map;
using std::map;
using std::string;
using std::shared_ptr;
using std::pair;
using std::forward_list;

class SceneFactory;


class GameManagerException : public ExplainedException
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
	TTF_Font* LoadFont(string assetName, int size);

	SDL_Renderer* GetRenderer();

	int m_mouseX, m_mouseY;
	int m_mouseLeft, m_mouseRight;
	Vector2d m_mouseLeftDownPoint;

	void AddObjectToRemove(shared_ptr<GameObject>  obj);
private:
	void Deinit();

	shared_ptr<GameObject> m_sceneRoot;
	
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Uint32 m_loopEndTime;
	SceneFactory& m_sceneFactory;
	unordered_map<string, SDL_Texture*> m_textures;
	map<pair<string,int>, TTF_Font *> m_fonts;
	forward_list<shared_ptr<GameObject>> m_toRemove;
	inline int MouseState(int curFromGm, int curFromSdl);
};

