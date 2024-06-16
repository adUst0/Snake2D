#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Sprite.h"
#include "engine/Text.h"
#include "SnakeBaseState.h"

// SDL includes

// std includes

class SplashState : public SnakeBaseState
{
public:
	SplashState(StateMachine& stateMachine);

	void							handleInput() override;
	void							draw() override;

private:
	Sprite							m_logo;
	Text							m_text;
};

