#pragma once
#include <SDL.h>
#include <string>
#include "Vector2d.h"
#include "Controller.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Update(Uint32 timeDelta);
	void Render();
private:
	std::string m_name;
	Vector2d m_position;
	Vector2d m_size;
	Controller m_controller;
	SDL_Texture* m_texture;
};

