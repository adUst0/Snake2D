// Local includes
#include "SplashState.h"
#include "GameSate.h"
#include "engine/Game.h"

// SDL includes
#include <SDL.h>

// std includes

SplashState::SplashState(StateMachine& stateMachine)
	: SnakeBaseState(stateMachine)
{
	AssetManager& assetManager = Game::getInstance().getAssetManager();
	assetManager.addTexture("snake2d_title", "assets/title.png");
	m_logo = Sprite::createSpriteCentered(assetManager.getTexture("snake2d_title"));

	m_text = Text::createTextCentered("Press any key or mouse button to start a new game!", Game::getInstance().getDefaultFont(24), { 255, 255, 255, 255 });
	m_text.offsetPosition({ 0, static_cast<int>(m_logo.getHeight() / 2.f) });
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
