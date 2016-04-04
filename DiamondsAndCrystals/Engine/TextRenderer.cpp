#include "TextRenderer.h"



TextRenderer::TextRenderer(SDL_Renderer* renderer) : m_renderer(renderer), m_texture(NULL)
{
}


TextRenderer::~TextRenderer()
{
	Free();
}

void TextRenderer::Render(SDL_Renderer* renderer, SDL_Rect* rect, float a)
{
	if (m_texture != NULL)
	{
		SDL_Rect target;
		target.x = rect->x;
		target.y = rect->y;
		target.w = m_width;
		target.h = m_height;
		Uint8 modA = 255.0*a;
		SDL_SetTextureAlphaMod(m_texture, modA);
		SDL_RenderCopy(m_renderer, m_texture, NULL, &target);
	}
}

void TextRenderer::SetFont(TTF_Font * font, SDL_Color  color)
{
	m_font = font;
	m_color = color;
}

void TextRenderer::SetText(const char * text)
{
	Free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text, m_color);
	if (textSurface != NULL)
	{
		m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		m_width = textSurface->w;
		m_height = textSurface->h;
		SDL_FreeSurface(textSurface);
	}
}

void TextRenderer::Free()
{
	if (m_texture != NULL)
		SDL_DestroyTexture(m_texture);
	m_texture = NULL;
}

