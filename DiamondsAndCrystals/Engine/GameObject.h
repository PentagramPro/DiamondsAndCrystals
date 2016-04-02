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
using std::shared_ptr;

class GameManager;
class Controller;

class GameObject : public std::enable_shared_from_this<GameObject>
{
	friend class GameManager;
public:
	
	virtual ~GameObject();

	void Update(Uint32 timeDelta);
	void Render();

	GameObject& CreateObject(const char* name, float x, float y, const char* textureAsset, Controller* controller);
	
	Vector2d m_localPosition;

	shared_ptr<GameObject> GetSharedPtr();

private:
	GameObject(GameManager& manager);
	GameObject(const char* name, float x, float y, int sizeX, int sizeY, GameManager& manager);

	Vector2d m_globalPosition;
	list<shared_ptr<GameObject>> m_children;
	shared_ptr<GameObject> m_parent;

	string m_name;
	SDL_Rect m_rect;
	shared_ptr<Controller> m_controller;
	SDL_Texture* m_texture;
	GameManager& m_manager;
};

