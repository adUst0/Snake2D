#pragma once

// Local includes
#include "engine/Drawable.h"
#include "WorldTypes.h"

// SDL includes
#include "SDL_pixels.h"

// std includes
#include <deque>

class World;

class Snake : public Drawable
{
public:
	enum class Direction
	{
		Right = 0,
		Down,
		Left,
		Up
	};

	Snake(World& wolrd);

	void							draw(SDL_Renderer& renderer) const override;

	void							tick(float dtSeconds);

	void							setColors(const SDL_Color& bodyColor, const SDL_Color& headColor);

	const WorldPosition&			getHeadPosition() const { return m_segments.front(); }
	const WorldPosition&			getTailPosition() const { return m_segments.back(); }

	bool							canChangeDirectionTo(Direction direction) const;
	void							changeDirection(Direction direction);
	Direction						getDirection() const { return m_direction; }

	bool							canAdvanceSnakePosition() const;
	void							advanceSnakePosition();

	void							setMoveTimeSeconds(float moveTimeSeconds) { m_moveTimeSeconds = moveTimeSeconds; }
	void							setMoveTimeSecondsCap(float moveTimeSecondsCap) { m_moveTimeSecondsCap = moveTimeSecondsCap; }
	void							setSpeedModifierPercentPerApple(float speedModifierPercentPerApple) { m_speedModifierPercentPerApple = speedModifierPercentPerApple; }

	int								numApplesCollected() const;

	void							setTeleportOnEdge(bool val) { m_shouldTeleportOnEdge = val; }

private:
	WorldPosition					calculateNextPosition() const;

	World*							m_world = nullptr;

	SDL_Color						m_bodyColor{ 0, 140, 50, 255 };
	SDL_Color						m_headColor{ 0, 62, 20, 255 };

	Direction						m_direction = Direction::Right;
	std::deque<WorldPosition>		m_segments;

	float							m_moveTimeSeconds = 0.2f;
	float							m_moveTimeSecondsCap = 0.f; // the speed of the snake cannot drop below this value
	float							m_speedModifierPercentPerApple = 0.1f;
	float							m_moveTimeLeft = m_moveTimeSeconds;
	bool							m_shouldTeleportOnEdge = false;
};

