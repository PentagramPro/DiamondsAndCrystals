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

	// This method is called by GameManager 
	// GameObject.Update calls Controller.Update and then GameObject.Update for all its children
	// timeDelta - time in milliseconds elapsed from previous call
	void Update(Uint32 timeDelta);

	// This method is called by GameManager
	// Render method calls Renderer.Render to display GameObject on the screen
	void Render();

	// Creates child GameObject with TextureRenderer
	GameObject& CreateObject(const char* name, float x, float y, const char* textureAsset, shared_ptr<Controller>  controller);

	// Creates child GameObject with custom Renderer
	GameObject& CreateObject(const char* name, float x, float y, int sizeX, int sizeY, shared_ptr<Renderer> renderer,
		shared_ptr<Controller>  controller);

	// position of GameObject relative to parent
	Vector2d m_localPosition;

	// returnes shared pointer to this GameObject
	shared_ptr<GameObject> GetSharedPtr();

	// Sets GameObject's texture
	// If GameObject does not have TextureRenderer, this method does nothing
	void SetTexture(string assetName);

	// Sets blending mode of this object
	// GameObject calls corresponding method of Renderer
	void SetBlendingMode(SDL_BlendMode mode);

	// Width and Height are either set up directly through CreateObject method or filled during texture loading
	int Width();
	int Height();

	GameManager& Manager() { return m_manager; }

	// returns true if mouse is inside this object
	bool IsMouseInside();

	// Enables or disables object and all its children
	// Disabled GameObject does not handle Update and Render calls
	// It disappears from the screen and does not update state
	// of its controller
	// This flag is NOT transferred to child GameObject. In other words they dont
	// change their state to disabled, but they also stop handling Update and Render calls
	void SetEnabled(bool isEnabled);

	// Schedules this object and all of its children for destruction
	// Destruction takes place at the end of Update cycle.
	void Destroy();

	// Sets or gets alpha value of the object [0-1].
	float m_alpha;
private:
	GameObject(GameManager& manager);
	GameObject(const char* name, float x, float y, int sizeX, int sizeY, GameManager& manager);

	// searches m_children for specified child and removes it
	// it doesn't free anything, just removes record from m_children
	void RemoveChild(shared_ptr<GameObject> child);

	// Recursively frees all shared pointers of this object and of its children
	// Calling this on destructed object prevents circular references
	void RemoveObject();

	// Position relative to root object
	// Updated from local position at  Update method
	Vector2d m_globalPosition;

	list<shared_ptr<GameObject>> m_children;

	
	shared_ptr<GameObject> m_parent;

	string m_name;

	// bounding rectangle
	// x,y are updated from local position
	// w,h are updated from constructor or from SetTexture
	SDL_Rect m_rect;

	// Linked controller
	// Controller contains game logic and has weak reference to this object
	shared_ptr<Controller> m_controller;

	// Object used to render this GameObject to the screen
	shared_ptr<Renderer> m_renderer;
	GameManager& m_manager;


	bool m_enabled;
};

