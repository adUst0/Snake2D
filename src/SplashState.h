#pragma once

// Local includes
#include "StateMachine.h"
#include "Sprite.h"
#include "Text.h"

// SDL includes

// std includes

class SplashState : public BaseState
{
public:
	SplashState(StateMachine& stateMachine);

	void							handleInput() override;
	void							draw() override;

private:
	Sprite							m_logo;
	Text							m_text;
};

