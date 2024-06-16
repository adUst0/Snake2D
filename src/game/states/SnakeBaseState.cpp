// Local includes
#include "SnakeBaseState.h"
#include "engine/Game.h"

// SDL includes
#include <SDL.h>
#include "GameSate.h"

// std includes

SnakeBaseState::SnakeBaseState(StateMachine& stateMachine)
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
}
