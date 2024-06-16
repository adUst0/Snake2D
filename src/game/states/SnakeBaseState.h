#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Sprite.h"
#include "engine/Text.h"

// SDL includes

// std includes

class SnakeBaseState : public BaseState
{
public:
	SnakeBaseState(StateMachine& stateMachine);

protected:
	Sprite							m_background;
};

