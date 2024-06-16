// Local includes
#include "StateMachine.h"
#include "Game.h"

// SDL includes
#include <SDL_events.h>

// std includes

BaseState::BaseState(StateMachine& stateMachine)
	: m_stateMachine(&stateMachine)
{
}

void BaseState::handleInput()
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			Game::getInstance().quit();
		}
	}
}

void StateMachine::pushState(std::unique_ptr<BaseState> newState, bool isReplacing /*= true*/)
{
	m_newState = std::move(newState);
	m_isReplacing = isReplacing;
}

void StateMachine::popState()
{
	m_isRemoving = true;
}

void StateMachine::processStateChanges()
{
	if (m_isRemoving && !m_states.empty())
	{
		m_states.top()->onLeaveState(false); // not pause
		m_states.pop();
		m_isRemoving = false;

		if (!m_states.empty())
		{
			m_states.top()->onEnterState(true); // resume
		}
	}

	if (m_newState)
	{
		if (!m_states.empty())
		{
			if (m_isReplacing)
			{
				m_states.top()->onLeaveState(false); // not pause
				m_states.pop();
			}
			else
			{
				m_states.top()->onLeaveState(true); // pause
			}
		}

		m_states.push(std::move(m_newState));
		m_states.top()->onEnterState(false); // not resume
	}
}

BaseState* StateMachine::getActiveState()
{
	return m_states.empty() ? nullptr : m_states.top().get();
}