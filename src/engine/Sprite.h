#pragma once

// Local includes

// SDL includes
#include <SDL.h>
#include "Drawable.h"

// std includes

class Sprite : public Drawable
{
public:
	void							setTexture(SDL_Texture& texture);

	const SDL_Rect&					getTextureRectangle() const { return m_textureRectangle; };
	SDL_Rect&						getTextureRectangle() { return m_textureRectangle; };

	void							setPosition(const SDL_Point& position) { m_position = position; }
	void							setScale(const SDL_FPoint& scale) { m_scale = scale; }

	virtual void					draw(SDL_Renderer& renderer) const override;

private:
	bool							m_isInitialized = false;

	SDL_Texture*					m_texture = nullptr;
	SDL_Rect						m_textureRectangle; // sub-rectangle of the texture. Can be used to show only part of the texture

	SDL_Point						m_position{ 0, 0 };
	SDL_FPoint						m_scale{ 1, 1 };
};