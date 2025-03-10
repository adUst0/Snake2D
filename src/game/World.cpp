// Local includes
#include "World.h"
#include "states/GameOverState.h"
#include "engine/Game.h"
#include "WorldTypes.h"

// SDL includes

// std includes
#include <stdlib.h>

World::World()
	: m_grid(GRID_ROWS, GRID_COLS, CELL_SIZE)
	, m_apple(*this)
	, m_snake(*this)
{
	m_grid.setColors(GRID_COLOR, GRID_COLOR_ALT);
	m_grid.setPosition({ SCREEN_X_PADDING, GRID_Y_OFFSET + SCREEN_Y_PADDING });

	m_snake.setColors(SNAKE_BODY_COLOR, SNAKE_HEAD_COLOR);
	m_snake.setMoveTimeSeconds(SNAKE_MOVE_TIME_SECONDS);
	m_snake.setMoveTimeSecondsCap(SNAKE_MOVE_TIME_SECONDS_CAP);
	m_snake.setSpeedModifierPercentPerApple(SNAKE_SPEED_MODIFIER_PERCENT_PER_APPLE);
	m_snake.setTeleportOnEdge(TELEPORT_SNAKE_ON_EDGE);

	moveAppleToRandomFreePosition();
}

void World::draw(SDL_Renderer& renderer) const
{
	m_grid.draw(renderer);
	m_apple.draw(renderer);
	m_snake.draw(renderer);
}

void World::onKeyPressed(const KeyEvent& event)
{
	switch (event)
	{
	case KeyEvent::Up:
		m_snake.changeDirection(Snake::Direction::Up);
		break;
	case KeyEvent::Right:
		m_snake.changeDirection(Snake::Direction::Right);
		break;
	case KeyEvent::Down:
		m_snake.changeDirection(Snake::Direction::Down);
		break;
	case KeyEvent::Left:
		m_snake.changeDirection(Snake::Direction::Left);
		break;
	default:
		break;
	}
}

void World::tick(float dtSeconds)
{
	m_snake.tick(dtSeconds);
}

void World::moveAppleToRandomFreePosition()
{
	static constexpr int MAX_ITERATIONS = 10000;
	for (int i = 0; i < MAX_ITERATIONS; ++i)
	{
		const int row = randRanged(0, m_grid.rows() - 1);
		const int col = randRanged(0, m_grid.cols() - 1);

		if (m_grid.getCellStatus(row, col) == CellStatus::Free)
		{
			m_apple.setWorldPosition({ row, col });
			return;
		}
	}

	// No free position for apple found
	notifyGameOver();
}

void World::notifyGameOver()
{
	Game::getInstance().getStateMachine().pushState(std::make_unique<GameOverState>(Game::getInstance().getStateMachine()));
}
