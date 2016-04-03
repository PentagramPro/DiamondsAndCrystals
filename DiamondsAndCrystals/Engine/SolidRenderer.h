#pragma once
#include "Renderer.h"

class SolidRenderer : public Renderer
{
public:
	SolidRenderer();
	virtual ~SolidRenderer();

	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
protected:
	SDL_Color m_color;
};

