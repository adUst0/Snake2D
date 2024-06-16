// Local includes
#include "Sprite.h"
#include "Game.h"

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

void Sprite::offsetPosition(const SDL_Point& offset)
{
	m_position.x += offset.x;
	m_position.y += offset.y;
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

Sprite Sprite::createSpriteCentered(SDL_Texture* texture)
{
	Sprite sprite;

	if (texture)
	{
		sprite.setTexture(*texture);
		const auto windowsSize = Game::getInstance().getWindowSize();
		const int x = static_cast<int>(windowsSize.x / 2.f - sprite.getWidth() / 2.f);
		const int y = static_cast<int>(windowsSize.y / 2.f - sprite.getHeight() / 2.f);
		sprite.setPosition({ x, y });
	}

	return sprite;
}
