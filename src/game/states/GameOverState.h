#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Text.h"
#include "SnakeBaseState.h"

// SDL includes

// std includes

class GameOverState : public SnakeBaseState
{
public:
	GameOverState(StateMachine& stateMachine);

	void							handleInput() override;
	void							draw() override;

private:
	Text							m_gameOverText;
	Text							m_newGameText;
};
