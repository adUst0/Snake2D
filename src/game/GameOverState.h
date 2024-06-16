#pragma once

// Local includes
#include "engine/StateMachine.h"

// SDL includes

// std includes

class GameOverState : public BaseState
{
public:
	GameOverState(StateMachine& stateMachine);

	void							draw() override;

private:
	
};
