// Local includes
#include "GameSate.h"
#include "Game.h"

// SDL includes

// std includes

GameSate::GameSate(StateMachine& stateMachine)
	: BaseState(stateMachine)
{
	AssetManager& assetManager = Game::getInstance().getAssetManager();
	assetManager.addFont("default", "assets/highland-gothic/HighlandGothicFLF.ttf", 24);
	TTF_Font* font = assetManager.getFont("default", 24);
	if (font)
	{
		m_text.initialize("Elapsed time ms: 0", *font);
	}
}

void GameSate::update(float dtSeconds)
{
	m_elapsedTime += dtSeconds;
	m_text.setText("Elapsed time seconds: " + std::to_string(m_elapsedTime));
}

void GameSate::draw()
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	m_text.draw(*renderer);

	SDL_RenderPresent(renderer);
}
