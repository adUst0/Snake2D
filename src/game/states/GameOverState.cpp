// Local includes
#include "GameOverState.h"
#include "engine/Game.h"
#include "GameSate.h"

// SDL includes

// std includes

GameOverState::GameOverState(StateMachine& stateMachine)
	: SnakeBaseState(stateMachine)
{
	m_gameOverText = Text::createTextCentered("Game Over!", Game::getInstance().getDefaultFont(72), { 255, 255, 255, 255 });

	static constexpr int yOffset = 10;
	m_newGameText = Text::createTextCentered("Press F5 to start a new game!", Game::getInstance().getDefaultFont(24), { 255, 255, 255, 255 });
	m_newGameText.offsetPosition({ 0, static_cast<int>(m_gameOverText.getHeight() / 2.f + yOffset) });
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
