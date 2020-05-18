#include "IntroState.h"
#include "PlayState.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	m_bgTexture.loadFromFile("../_external/img/bg.png");
	m_bg.setTexture(m_bgTexture, true);

	if (!m_font.loadFromFile("../_external/font/bm.ttf"))
	{
		// handle error
	}

	m_menu[0].setFont(m_font);
	m_menu[0].setFillColor(sf::Color::White);
	m_menu[0].setString("Press ENTER for New Game...");
	m_menu[0].setPosition(sf::Vector2f(window.getPosition().x - 500, window.getPosition().y - 60));
	m_menu[0].setScale(0.8, 0.8);

	m_menu[1].setFont(m_font);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setString("or ESC to Exit!");
	m_menu[1].setPosition(sf::Vector2f(window.getPosition().x - 500, window.getPosition().y - 35));
	m_selectedItemIndex = 0;
	m_menu[1].setScale(0.6, 0.6);

	std::cout << "IntroState Ctor" << std::endl;
}

void IntroState::Update()
{
	sf::Event event;
	sf::View view;

	while (m_window.pollEvent(event))
	{

		//////

		if (event.type == sf::Event::Resized)
		{
			auto window_width = event.size.width;
			auto window_height = event.size.height;

			float new_width = window_height;
			float new_height = window_width;
			float offset_width = (window_width - new_width) / 2.0;
			float offset_height = (window_height - new_height) / 2.0;

			sf::View view = m_window.getDefaultView();

			if (window_width < 816 || window_height < 816)
			{
				view.setViewport(sf::FloatRect(0.f, 0.f, 816.f, 816.f));
				m_window.setSize(sf::Vector2u(816, 816));
				m_window.setPosition(sf::Vector2i(400, 200));
			}
			else
			{
				if (window_width >= window_height)
				{
					view.setViewport(sf::FloatRect(offset_width / window_width, 0.0, new_width / window_width, 1.0));
				}
				else
				{
					view.setViewport(sf::FloatRect(0.0, offset_height / window_height, 1.0, new_height / window_height));
				}

			}

			m_window.setView(view);
		}

		//////

		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.Quit();
			break;

		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Enter:
				m_next = StateMachine::Build<PlayState>(m_machine, m_window, true);
				break;

			case sf::Keyboard::Escape:
				m_machine.Quit();
				break;

			default:
				break;
			}
			break;
		}

		default:
			break;
		}
	}
}

void IntroState::Pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::Resume()
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);

	for (int i = 0; i < 2; i++)
	{
		m_window.draw(m_menu[i]);
	}

	m_window.display();
}