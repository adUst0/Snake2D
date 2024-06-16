// Local includes
#include "Sprite.h"

// SDL includes

// std includes

void Sprite::setTexture(SDL_Texture& texture)
{
	m_texture = &texture;

	SDL_Point size;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &size.x, &size.y);
	m_textureRectangle = { 0, 0, size.x, size.y };

	m_isInitialized = true;
}

void Sprite::draw(SDL_Renderer& renderer) const
{
	if (!m_isInitialized)
	{
		return;
	}

	SDL_Rect drect = { m_position.x, m_position.y, static_cast<int>(m_textureRectangle.w * m_scale.x), static_cast<int>(m_textureRectangle.h * m_scale.y) };
	SDL_RenderCopy(&renderer, m_texture, &m_textureRectangle, &drect);
}
