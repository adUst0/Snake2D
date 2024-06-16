// Local includes
#include "Text.h"
#include "Game.h"

// SDL includes

// std includes

Text::Text(Text&& rhs) noexcept
{
	move(std::move(rhs));
}

Text& Text::operator=(Text&& rhs) noexcept
{
	if (&rhs != this)
	{
		move(std::move(rhs));
	}

	return *this;
}

void Text::move(Text&& rhs)
{
	m_surface = rhs.m_surface;
	m_texture = rhs.m_texture;
	m_font = rhs.m_font;
	m_color = std::move(rhs.m_color);
	m_text = std::move(rhs.m_text);
	m_sprite = std::move(rhs.m_sprite);

	rhs.m_surface = nullptr;
	rhs.m_texture = nullptr;
	rhs.m_font = nullptr;
}

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

void Text::setColor(const SDL_Color& color)
{
	m_color = color;
	if (isInitialized())
	{
		setText(m_text); // reinitialize
	}
}

void Text::offsetPosition(const SDL_Point& offset)
{
	m_sprite.offsetPosition(offset);
}

const SDL_Point& Text::getPosition() const
{
	return m_sprite.getPosition();
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

Text Text::createTextCentered(const std::string& str, TTF_Font* font, const SDL_Color& color /*= { 0, 0, 0 }*/)
{
	Text text;

	if (font)
	{
		text.setColor(color);
		text.initialize(str, *font);
		const auto windowsSize = Game::getInstance().getWindowSize();
		const int x = static_cast<int>(windowsSize.x / 2.f - text.getSprite().getTextureRectangle().w / 2.f);
		const int y = static_cast<int>(windowsSize.y / 2.f - text.getSprite().getTextureRectangle().h / 2.f);
		text.setPosition({ x, y });
	}

	return text;
}
