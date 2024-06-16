#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Text.h"
#include "../World.h"
#include "SnakeBaseState.h"

// SDL includes

// std includes

class GameSate : public SnakeBaseState
{
public:
	GameSate(StateMachine& stateMachine);


	void							handleInput() override;
	virtual void					update(float dtSeconds) override;
	void							draw() override;

private:

	float							m_elapsedTime = 0.f;
	float							m_elapsedTimeUpdateInterval = 0.1f;
	float							m_elapsedTimeSecondsTillNextUpdate = m_elapsedTimeUpdateInterval;
	Text							m_elapsedTimeText;
	Text							m_applesCollectedText;
	Text							m_pauseInfoText;

	Text							m_pauseText;
	bool							m_isPaused = false;

	Sprite							m_controls;

	World							m_world;

	static constexpr int			S_TEXT_OFFSSET = 5;
};

