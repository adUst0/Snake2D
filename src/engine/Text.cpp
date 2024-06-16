// Local includes
#include "Text.h"
#include "Game.h"

// SDL includes

// std includes

Text::~Text()
{
	freeResources();
}

void Text::freeResources()
{
	if (m_surface)
	{
		SDL_FreeSurface(m_surface);
	}

	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

void Text::initialize(const std::string& text, TTF_Font& font)
{
	if (isInitialized())
	{
		return;
	}

	m_font = &font;

	setText(text);	
}

void Text::setText(const std::string& text)
{
	if (!isInitialized())
	{
		return;
	}

	m_text = text;

	freeResources();
	m_surface = TTF_RenderText_Solid(m_font, text.c_str(), m_color);
	m_texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), m_surface);

	m_sprite.setTexture(*m_texture);
}

void Text::setPosition(const SDL_Point& position)
{
	m_sprite.setPosition(position);
}

void Text::draw(SDL_Renderer& renderer) const
{
	if (!isInitialized())
	{
		return;
	}

	m_sprite.draw(renderer);
}
