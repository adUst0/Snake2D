#pragma once

// Local includes
#include "Utils.h"

// SDL includes

// std includes
#include <memory>
#include <stack>

class StateMachine;

class BaseState : public NonCopyableAndNonMovable
{
public:
	BaseState(StateMachine& stateMachine);
	virtual ~BaseState() = default;

	virtual void					onEnterState(bool /*isResume*/) {}
	virtual void					onLeaveState(bool /*isPause*/) {}

	virtual void					handleInput();
	virtual void					update(float /*dtSeconds*/) {}
	virtual void					draw() {};

protected:
	StateMachine*					m_stateMachine;
};

class StateMachine
{
public:
	StateMachine() = default;

	void							pushState(std::unique_ptr<BaseState> newState, bool isReplacing = true);
	void							popState();

	void							processStateChanges();

	BaseState*						getActiveState();

private:

	std::stack<std::unique_ptr<BaseState>> m_states;
	std::unique_ptr<BaseState>		m_newState;

	bool							m_isRemoving = false;
	bool							m_isReplacing = false;
};