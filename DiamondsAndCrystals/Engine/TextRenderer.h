#pragma once
#include "Renderer.h"
#include <string>
#include <SDL_ttf.h>

using std::string;

class TextRenderer :
	public Renderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	virtual ~TextRenderer();

	virtual void Render(SDL_Renderer* renderer, SDL_Rect* rect);
	void SetFont(TTF_Font* font, SDL_Color color);
	void SetText(const char* text);
protected:
	SDL_Texture* m_texture;
	SDL_Color m_color;
	TTF_Font* m_font;
	SDL_Renderer* m_renderer;
	int m_width, m_height;
	void Free();
};

