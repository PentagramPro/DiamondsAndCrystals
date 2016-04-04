#pragma once
#include <SDL.h>
#include <string>
#include <list>
#include <memory>

#include "Vector2d.h"
#include "Controller.h"
#include "GameManager.h"
#include "Renderer.h"

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

	// Creates child GameObject with TextureRenderer
	GameObject& CreateObject(const char* name, float x, float y, const char* textureAsset, shared_ptr<Controller>  controller);

	// Creates child GameObject with custom Renderer
	GameObject& CreateObject(const char* name, float x, float y, int sizeX, int sizeY, shared_ptr<Renderer> renderer,
		shared_ptr<Controller>  controller);
	Vector2d m_localPosition;

	shared_ptr<GameObject> GetSharedPtr();

	// Sets GameObject's texture
	// If GameObject does not have TextureRenderer, this method does nothing
	void SetTexture(string assetName);

	void SetBlendingMode(SDL_BlendMode mode);

	int Width();
	int Height();
	GameManager& Manager() { return m_manager; }

	bool IsMouseInside();
	void SetEnabled(bool isEnabled);

	void Destroy();
	float m_alpha;
private:
	GameObject(GameManager& manager);
	GameObject(const char* name, float x, float y, int sizeX, int sizeY, GameManager& manager);


	void RemoveChild(shared_ptr<GameObject> child);
	void RemoveObject();

	Vector2d m_globalPosition;
	list<shared_ptr<GameObject>> m_children;
	shared_ptr<GameObject> m_parent;

	string m_name;
	SDL_Rect m_rect;
	shared_ptr<Controller> m_controller;
	shared_ptr<Renderer> m_renderer;
	GameManager& m_manager;
	bool m_enabled;
};

