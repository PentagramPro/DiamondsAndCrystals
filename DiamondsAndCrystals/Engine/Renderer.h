#pragma once

#include <SDL.h>
class Renderer
{
public:
	
	virtual ~Renderer() ;


	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect, float a) = 0;

	virtual void SetBlendingMode(SDL_BlendMode mode) {}
};

