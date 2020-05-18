#include "Application.h"

void Application::Run()
{
	// Create render window
	m_window.create(sf::VideoMode(m_windowSize, m_windowSize + 48), ' ', sf::Style::Resize);
	m_window.setFramerateLimit(m_framesPerSecond);

	// Initialize the engine
	m_machine.Run(StateMachine::Build<IntroState>(m_machine, m_window, true));

	// Main loop
	while (m_machine.Running())
	{
		m_machine.NextState();
		m_machine.Update();
		m_machine.Draw();
	}
}