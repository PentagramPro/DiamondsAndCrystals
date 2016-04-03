#include "TextureRenderer.h"



TextureRenderer::TextureRenderer()
{
}


TextureRenderer::~TextureRenderer()
{
}

void TextureRenderer::Render(SDL_Renderer* renderer, SDL_Rect* rect)
{
	if (m_texture != NULL)
		SDL_RenderCopy(renderer, m_texture, NULL, rect);

}

void TextureRenderer::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
}

