#pragma once
#include "Renderer.h"
class TextureRenderer :
	public Renderer
{
public:
	TextureRenderer();
	virtual ~TextureRenderer();

	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect);

	void SetTexture(SDL_Texture* texture);
	
protected:
	SDL_Texture* m_texture;
};

