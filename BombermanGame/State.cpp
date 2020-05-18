#include "State.h"

State::State(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	m_machine(machine), m_window(window), m_replacing(replace)
{
	// empty
}

std::unique_ptr<State> State::Next()
{
	return std::move(m_next);
}

bool State::isReplacing()
{
	return m_replacing;
}
