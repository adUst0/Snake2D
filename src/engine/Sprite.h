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

	int								getHeight() const { return m_textureRectangle.h; }
	int								getWidth() const { return m_textureRectangle.w; }

	const SDL_Point&				getPosition() const { return m_position; }
	void							setPosition(const SDL_Point& position) { m_position = position; }
	void							offsetPosition(const SDL_Point& offset);
	void							setScale(const SDL_FPoint& scale) { m_scale = scale; }

	virtual void					draw(SDL_Renderer& renderer) const override;

	static Sprite					createSpriteCentered(SDL_Texture* texture);

private:
	bool							m_isInitialized = false;

	SDL_Texture*					m_texture = nullptr;
	SDL_Rect						m_textureRectangle; // dimensions of texture. Can be used to show only part of the texture

	SDL_Point						m_position{ 0, 0 };
	SDL_FPoint						m_scale{ 1, 1 };
};