// Local includes
#include "Apple.h"
#include "engine/Game.h"
#include "World.h"

// SDL includes

// std includes

Apple::Apple(World& world)
	: m_world(&world)
{
	AssetManager& assetManager = Game::getInstance().getAssetManager();
	assetManager.addTexture("apple", "assets/apple.png");
	if (SDL_Texture* texture = assetManager.getTexture("apple"))
	{
		m_sprite.setTexture(*texture);
		const SDL_Rect rect = m_sprite.getTextureRectangle();
		const float scaleX = m_world->getGrid().getCellSize() / (float)rect.w;
		const float scaleY = m_world->getGrid().getCellSize() / (float)rect.h;
		m_sprite.setScale({ scaleX, scaleY });
	}
}

void Apple::draw(SDL_Renderer& renderer) const
{
	m_sprite.draw(renderer);
}

void Apple::setWorldPosition(const WorldPosition& pos)
{
	if (m_worldPosition.row != -1 && m_worldPosition.col != -1)
	{
		m_world->getGrid().setCellType(m_worldPosition.row, m_worldPosition.col, CellType::Free);
	}

	m_worldPosition = pos;
	m_world->getGrid().setCellType(m_worldPosition.row, m_worldPosition.col, CellType::Apple);

	const auto globalPos = m_world->getGrid().getCellPosition(m_worldPosition.row, m_worldPosition.col);
	m_sprite.setPosition({ (int)globalPos.x, (int)globalPos.y });
}
