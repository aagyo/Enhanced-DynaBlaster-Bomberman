#include "StateMachine.h"
#include "Logger.h"

StateMachine::StateMachine() :
	m_resumeState(false), m_runningState(false)
{
	if (globalLogger.initialized == false)
	{
		globalLogger.InitLogger("globalLogger.txt", LogOutput::everywhere);
		globalLogger.initialized = true;
		globalLogger.OpenLogger();
		globalLogger.LogData("Logger has been initialized", LogSeverity::info);
	}
}

void StateMachine::Run(std::unique_ptr<State> state)
{
	m_runningState = true;
	m_states.push(std::move(state));
}

void StateMachine::NextState()
{
	if (m_resumeState)
	{
		// Cleanup the current state
		if (!m_states.empty())
		{
			m_states.pop();
		}

		// Resume previous state
		if (!m_states.empty())
		{
			m_states.top()->Resume();
		}

		m_resumeState = false;
	}

	// There needs to be a state
	if (!m_states.empty())
	{
		std::unique_ptr<State> nextState = m_states.top()->Next();

		// Only change states if there's a next one existing
		if (nextState != nullptr)
		{
			// Replace the running state
			if (nextState->isReplacing())
			{
				m_states.pop();
			}
			// Pause the running state
			else
			{
				m_states.top()->Pause();
			}

			m_states.push(std::move(nextState));
		}
	}
}

void StateMachine::LastState()
{
	m_resumeState = true;
}

void StateMachine::Update()
{
	// Let the state update the game
	m_states.top()->Update();
}

void StateMachine::Draw()
{
	// Let the state draw the screen
	m_states.top()->Draw();
}

bool StateMachine::Running() const
{
	return m_runningState;
}

void StateMachine::Quit()
{
	m_runningState = false;
}