// Local includes
#include "SplashState.h"
#include "engine/Game.h"
#include "Config.h"

// SDL includes
#include <SDL.h>
#include "GameSate.h"

// std includes

SplashState::SplashState(StateMachine& stateMachine)
	: BaseState(stateMachine)
{
	const auto windowsSize = Game::getInstance().getWindowSize();

	AssetManager& assetManager = Game::getInstance().getAssetManager();

	assetManager.addTexture("background", "assets/background.jpg");
	if (SDL_Texture* texture = assetManager.getTexture("background"))
	{
		m_background.setTexture(*texture);
		const SDL_Rect rect = m_background.getTextureRectangle();
		const float scaleX = windowsSize.x / (float)rect.w;
		const float scaleY = windowsSize.y / (float)rect.h;
		m_background.setScale({ scaleX, scaleY });
	}

	assetManager.addTexture("snake2d_title", "assets/title.png");
	SDL_Texture* texture = assetManager.getTexture("snake2d_title");
	if (texture)
	{
		m_logo.setTexture(*texture);
		const int x = static_cast<int>(windowsSize.x / 2.f - m_logo.getTextureRectangle().w / 2.f);
		const int y = static_cast<int>(windowsSize.y / 2.f - m_logo.getTextureRectangle().h / 2.f);
		m_logo.setPosition({ x, y });
	}

	assetManager.addFont("default", "assets/highland-gothic/HighlandGothicFLF.ttf", 24);
	TTF_Font* font = assetManager.getFont("default", 24);
	if (font)
	{
		m_text.setColor({ 255, 255, 255, 255 });
		m_text.initialize("Press any key or mouse button to start a new game!", *font);

		const auto windowsSize = Game::getInstance().getWindowSize();
		const int x = static_cast<int>(windowsSize.x / 2.f - m_text.getSprite().getTextureRectangle().w / 2.f);
		const int y = static_cast<int>(windowsSize.y / 2.f - m_text.getSprite().getTextureRectangle().h / 2.f + m_logo.getTextureRectangle().h / 2.f);
		m_text.setPosition({ x, y });
	}
}

void SplashState::handleInput()
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Game::getInstance().quit();
		}
		else if (e.type == SDL_KEYUP || e.type == SDL_MOUSEBUTTONUP)
		{
			m_stateMachine->pushState(std::make_unique<GameSate>(*m_stateMachine));
		}
	}
}

void SplashState::draw()
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	m_background.draw(*renderer);
	m_logo.draw(*renderer);
	m_text.draw(*renderer);

	SDL_RenderPresent(renderer);
}
