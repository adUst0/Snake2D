#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Text.h"

// SDL includes

// std includes

class GameOverState : public BaseState
{
public:
	GameOverState(StateMachine& stateMachine);

	void							handleInput() override;
	void							draw() override;

private:
	Sprite							m_background;
	Text							m_gameOverText;
	Text							m_newGameText;
};
