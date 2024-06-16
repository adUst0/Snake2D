// Local includes
#include "GameSate.h"
#include "engine/Game.h"

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
		m_text.setPosition({ SCREEN_X_PADDING, SCREEN_Y_PADDING });
	}

	assetManager.addTexture("background", "assets/background.jpg");
	if (SDL_Texture* texture = assetManager.getTexture("background"))
	{
		m_background.setTexture(*texture);
		const SDL_Rect rect = m_background.getTextureRectangle();
		const float scaleX = SCREEN_WIDTH / (float)rect.w;
		const float scaleY = SCREEN_HEIGHT/ (float)rect.h;
		m_background.setScale({ scaleX, scaleY });
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

	m_background.draw(*renderer);
	m_text.draw(*renderer);

	m_world.draw(*renderer);

	SDL_RenderPresent(renderer);
}
