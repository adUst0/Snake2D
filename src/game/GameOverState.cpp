// Local includes
#include "GameOverState.h"
#include "engine/Game.h"

// SDL includes

// std includes

GameOverState::GameOverState(StateMachine& stateMachine)
	: BaseState(stateMachine)
{

}

void GameOverState::draw()
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
