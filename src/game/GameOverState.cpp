// Local includes
#include "GameOverState.h"
#include "engine/Game.h"
#include "GameSate.h"

// SDL includes

// std includes

GameOverState::GameOverState(StateMachine& stateMachine)
	: BaseState(stateMachine)
{
	AssetManager& assetManager = Game::getInstance().getAssetManager();

	assetManager.addTexture("background", "assets/background.jpg");
	if (SDL_Texture* texture = assetManager.getTexture("background"))
	{
		m_background.setTexture(*texture);
		const SDL_Rect rect = m_background.getTextureRectangle();
		const auto windowsSize = Game::getInstance().getWindowSize();
		const float scaleX = windowsSize.x / (float)rect.w;
		const float scaleY = windowsSize.y / (float)rect.h;
		m_background.setScale({ scaleX, scaleY });
	}

	assetManager.addFont("default", "assets/highland-gothic/HighlandGothicFLF.ttf", 72);
	TTF_Font* font = assetManager.getFont("default", 72);
	if (font)
	{
		m_gameOverText.setColor({ 255, 255, 255, 255 });
		m_gameOverText.initialize("Game Over!", *font);

		const auto windowsSize = Game::getInstance().getWindowSize();
		const int x = static_cast<int>(windowsSize.x / 2.f - m_gameOverText.getSprite().getTextureRectangle().w / 2.f);
		const int y = static_cast<int>(windowsSize.y / 2.f - m_gameOverText.getSprite().getTextureRectangle().h / 2.f);
		m_gameOverText.setPosition({ x, y });
	}

	font = assetManager.getFont("default", 24);
	if (font)
	{
		m_newGameText.setColor({ 255, 255, 255, 255 });
		m_newGameText.initialize("Press F5 to start a new game!", *font);

		static constexpr int yOffset = 10;
		const auto windowsSize = Game::getInstance().getWindowSize();
		const int x = static_cast<int>(windowsSize.x / 2.f - m_newGameText.getSprite().getTextureRectangle().w / 2.f);
		const int y = yOffset + static_cast<int>(windowsSize.y / 2.f - m_newGameText.getSprite().getTextureRectangle().h / 2.f + m_gameOverText.getSprite().getTextureRectangle().h / 2.f);
		m_newGameText.setPosition({ x, y });
	}
}

void GameOverState::handleInput()
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Game::getInstance().quit();
		}
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F5)
		{
			m_stateMachine->pushState(std::make_unique<GameSate>(*m_stateMachine));
		}
	}
}

void GameOverState::draw()
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	m_background.draw(*renderer);
	m_gameOverText.draw(*renderer);
	m_newGameText.draw(*renderer);

	SDL_RenderPresent(renderer);
}
