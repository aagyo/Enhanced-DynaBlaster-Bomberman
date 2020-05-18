#include "Application.h"
#include "IntroState.h"

void Application::Run()
{
	m_window.create(sf::VideoMode(m_windowSizeWidth, m_windowSizeHeight), ' ', sf::Style::Resize);
	m_window.setFramerateLimit(m_framesPerSecond);

	m_machine.Run(StateMachine::Build<IntroState>(m_machine, m_window, true));

	while (m_machine.Running())
	{
		m_machine.NextState();
		m_machine.Update();
		m_machine.Draw();
	}
}