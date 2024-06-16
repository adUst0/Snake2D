#pragma once

// Local includes
#include "Sprite.h"

// SDL includes
#include <SDL_pixels.h>
#include <SDL_ttf.h>

// std includes
#include <string>
#include "Utils.h"

struct SDL_Texture;
struct SDL_Surface;

class Text 
	: public NonCopyable
	, public Drawable
{
public:
	Text() = default;
	Text(Text&&) noexcept;
	Text& operator=(Text&&) noexcept;

	~Text();

	void							initialize(const std::string& text, TTF_Font& font);

	const std::string&				getText() const { return m_text; }
	void							setText(const std::string& text);

	void							setColor(const SDL_Color& color);

	int								getHeight() const { return m_sprite.getHeight(); }
	int								getWidth() const { return m_sprite.getWidth(); }

	void							offsetPosition(const SDL_Point& offset);
	const SDL_Point&				getPosition() const;
	void							setPosition(const SDL_Point& position);

	const Sprite&					getSprite() const { return m_sprite; }

	virtual void					draw(SDL_Renderer& renderer) const override;

	static Text						createTextCentered(const std::string& str, TTF_Font* font, const SDL_Color& color = { 0, 0, 0 });

private:
	void							move(Text&& rhs);
	void							freeResources();
	bool							isInitialized() const { return m_font != nullptr; }

	SDL_Surface*					m_surface = nullptr;
	SDL_Texture*					m_texture = nullptr;
	TTF_Font*						m_font = nullptr;
	Sprite							m_sprite;

	SDL_Color						m_color{ 0, 0, 0 };
	std::string						m_text;
};

