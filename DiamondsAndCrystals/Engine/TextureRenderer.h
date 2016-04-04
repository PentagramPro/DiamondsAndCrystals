#pragma once
#include "Renderer.h"
class TextureRenderer :
	public Renderer
{
public:
	TextureRenderer();
	virtual ~TextureRenderer();

	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect, float a);
	virtual void SetBlendingMode(SDL_BlendMode mode);

	void SetTexture(SDL_Texture* texture);
	
protected:
	SDL_Texture* m_texture;
};

