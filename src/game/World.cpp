// Local includes
#include "World.h"
#include "GameOverState.h"
#include "engine/Game.h"

// SDL includes

// std includes
#include <stdlib.h>

World::World()
	: m_grid(CELL_SIZE)
	, m_apple(*this)
{
	m_grid.setColors(GRID_COLOR, GRID_COLOR_ALT);
	m_grid.setPosition({ SCREEN_X_PADDING, GRID_Y_OFFSET + SCREEN_Y_PADDING });

	moveAppleToRandomFreePosition();
}

void World::draw(SDL_Renderer& renderer) const
{
	m_grid.draw(renderer);
	m_apple.draw(renderer);
}

void World::moveAppleToRandomFreePosition()
{
	static constexpr int MAX_ITERATIONS = 10000;
	for (int i = 0; i < MAX_ITERATIONS; ++i)
	{
		const int row = rand() % m_grid.rows();
		const int col = rand() % m_grid.cols();

		if (m_grid.getCellType(row, col) == CellType::Free)
		{
			m_apple.setWorldPosition({ row, col });
			return;
		}
	}

	// No free position for apple found
	Game::getInstance().getStateMachine().pushState(std::make_unique<GameOverState>(Game::getInstance().getStateMachine()));
}
