#pragma once

#include <SDL.h>
class Renderer
{
public:
	
	virtual ~Renderer() ;


	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect) = 0;
};

