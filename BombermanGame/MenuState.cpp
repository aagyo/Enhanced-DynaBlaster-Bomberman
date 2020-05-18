#include "MenuState.h"
#include "IntroState.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	m_bgTexture.loadFromFile("../_external/img/pause.png");
	m_bg.setTexture(m_bgTexture, true);

	m_alpha = sf::Color(0, 0, 0, 255);
	m_fader.setFillColor(m_alpha);
	m_fader.setSize(static_cast<sf::Vector2f>(m_bgTexture.getSize()));

	std::cout << "MenuState Ctor" << std::endl;
}

void MenuState::Pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::Resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MenuState::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.Quit();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::C:
				m_machine.LastState();
				break;

			case sf::Keyboard::I:
				m_next = StateMachine::Build<IntroState>(m_machine, m_window, true);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	if (m_alpha.a > 0)
	{
		m_alpha.a -= 1;
	}
	m_fader.setFillColor(m_alpha);
}

void MenuState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);

	if (m_alpha.a != 0)
	{
		m_window.draw(m_fader);
	}

	m_window.display();
}
