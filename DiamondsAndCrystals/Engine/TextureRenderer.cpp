#include "TextureRenderer.h"



TextureRenderer::TextureRenderer()
{
}


TextureRenderer::~TextureRenderer()
{
}

void TextureRenderer::Render(SDL_Renderer* renderer, SDL_Rect* rect, float a)
{
	if (m_texture != NULL)
	{
		Uint8 modA = 255.0*a;
		SDL_SetTextureAlphaMod(m_texture, modA);
		SDL_RenderCopy(renderer, m_texture, NULL, rect);
	}

}

void TextureRenderer::SetBlendingMode(SDL_BlendMode mode)
{
	SDL_SetTextureBlendMode(m_texture, mode);
}

void TextureRenderer::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
}

