#pragma once

// Local includes
#include "engine/StateMachine.h"
#include "engine/Text.h"
#include "World.h"

// SDL includes

// std includes

class GameSate : public BaseState
{
public:
	GameSate(StateMachine& stateMachine);



	virtual void					update(float dtSeconds) override;
	void							draw() override;

private:

	// TODO testing. delete
	float							m_elapsedTime = 0.f;
	Text							m_text;
	Sprite							m_background;

	World							m_world;
};

