#include "SolidRenderer.h"



SolidRenderer::SolidRenderer()
{
}


SolidRenderer::~SolidRenderer()
{
}

void SolidRenderer::Render(SDL_Renderer * renderer, SDL_Rect * rect)
{
	SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, rect);
	
}

void SolidRenderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}


