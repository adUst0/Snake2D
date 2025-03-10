// Local includes
#include "Snake.h"
#include "World.h"

// SDL includes
#include <SDL.h>

// std includes

Snake::Snake(World& wolrd)
	: m_world(&wolrd)
{
	m_segments.emplace_back(WorldPosition{ 0, 1 });
	m_world->getGrid().setCellStatus(0, 1, CellStatus::Snake);

	m_segments.emplace_back(WorldPosition{ 0, 0 });
	m_world->getGrid().setCellStatus(0, 0, CellStatus::Snake);
}

void Snake::draw(SDL_Renderer& renderer) const
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(&renderer, &r, &g, &b, &a);

	bool headDrawn = false;
	for (auto& [row, col] : m_segments)
	{
		const SDL_Color& color = getHeadPosition().row == row && getHeadPosition().col == col ? m_headColor : m_bodyColor;
		SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);

		const auto cellPos = m_world->getGrid().getCellPosition(row, col);
		const float cellSize = static_cast<float>(m_world->getGrid().getCellSize());
		const SDL_FRect rect{ cellPos.x, cellPos.y, cellSize, cellSize };
		SDL_RenderFillRectF(&renderer, &rect);
	}

	SDL_SetRenderDrawColor(&renderer, r, g, b, a);
}

void Snake::tick(float dtSeconds)
{
	m_moveTimeLeft -= dtSeconds;
	if (m_moveTimeLeft <= 0)
	{
		m_moveTimeLeft = m_moveTimeSeconds;
		advanceSnakePosition();
	}
}

void Snake::setColors(const SDL_Color& bodyColor, const SDL_Color& headColor)
{
	m_bodyColor = bodyColor;
	m_headColor = headColor;
}

bool Snake::canChangeDirectionTo(Direction direction) const
{
	return m_direction == Direction::Down || m_direction == Direction::Up ?
		direction == Direction::Left || direction == Direction::Right :
		direction == Direction::Down || direction == Direction::Up;
}

void Snake::changeDirection(Direction direction)
{
	if (!canChangeDirectionTo(direction))
	{
		return;
	}

	m_direction = direction;
}

bool Snake::canAdvanceSnakePosition() const
{
	const WorldPosition newPos = calculateNextPosition();
	if (!m_world->getGrid().isValidCell(newPos.row, newPos.col))
	{
		return false;
	}

	const CellStatus status = m_world->getGrid().getCellStatus(newPos.row, newPos.col);
	return status == CellStatus::Free || status == CellStatus::Apple;
}

void Snake::advanceSnakePosition()
{
	if (canAdvanceSnakePosition())
	{
		WorldPosition newPos = calculateNextPosition();
		const bool hitApple = m_world->getGrid().getCellStatus(newPos.row, newPos.col) == CellStatus::Apple;
		m_world->getGrid().setCellStatus(newPos.row, newPos.col, CellStatus::Snake);
		m_segments.emplace_front(std::move(newPos));

		if (hitApple)
		{
			m_world->moveAppleToRandomFreePosition();
			const float newMoveTime = m_moveTimeSeconds * (1.f - m_speedModifierPercentPerApple);
			m_moveTimeSeconds = std::max(newMoveTime, m_moveTimeSecondsCap);
		}
		else
		{
			m_world->getGrid().setCellStatus(getTailPosition().row, getTailPosition().col, CellStatus::Free);
			m_segments.pop_back();
		}
	}
	else
	{
		m_world->notifyGameOver();
	}
}

int Snake::numApplesCollected() const
{
	static constexpr int defaultSize = 2;
	return (int)m_segments.size() - defaultSize;
}

WorldPosition Snake::calculateNextPosition() const
{
	WorldPosition headPosition = getHeadPosition();

	switch (m_direction)
	{
	case Snake::Direction::Right:
		++headPosition.col;
		break;
	case Snake::Direction::Down:
		++headPosition.row;
		break;
	case Snake::Direction::Left:
		--headPosition.col;
		break;
	case Snake::Direction::Up:
		--headPosition.row;
		break;
	default:
		break;
	}

	if (m_shouldTeleportOnEdge)
	{
		if (headPosition.row >= m_world->getGrid().rows())
		{
			headPosition.row = 0;
		}
		else if (headPosition.row < 0)
		{
			headPosition.row = m_world->getGrid().rows() - 1;
		}

		if (headPosition.col >= m_world->getGrid().cols())
		{
			headPosition.col = 0;
		}
		else if (headPosition.col < 0)
		{
			headPosition.col = m_world->getGrid().cols() - 1;
		}
	}

	return headPosition;
}
