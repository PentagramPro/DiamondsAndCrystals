#pragma once
#include <SDL.h>
#include <string>
#include <list>
#include <memory>

#include "Vector2d.h"
#include "Controller.h"
#include "GameManager.h"

using std::string;
using std::list;
using std::unique_ptr;

class GameManager;

class GameObject
{
	friend class GameManager;
public:
	
	virtual ~GameObject();

	void Update(Uint32 timeDelta);
	void Render();

	GameObject& CreateObject(const char* name, int x, int y, const char* textureAsset, Controller* controller);
	
private:
	GameObject(GameManager& manager);
	GameObject(const char* name, int x, int y, int sizeX, int sizeY, GameManager& manager);

	list<unique_ptr<GameObject>> m_children;
	string m_name;
	SDL_Rect m_rect;
	Controller* m_controller;
	SDL_Texture* m_texture;
	GameManager& m_manager;
};

