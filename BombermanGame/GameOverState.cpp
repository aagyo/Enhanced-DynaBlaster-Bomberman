#include "GameOverState.h"
#include "IntroState.h"
#include "LevelState.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

GameOverState::GameOverState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	m_bgTexture.loadFromFile("../_external/states/gameoverstate.png");
	m_bg.setTexture(m_bgTexture, true);

	m_soundBuffer.loadFromFile("../_external/audio/gameover.flac");
	m_sound.setBuffer(m_soundBuffer);
	m_sound.play();
	m_sound.setLoop(true);

	std::cout << "GameOverState Ctor" << std::endl;
}
void GameOverState::Pause()
{
	std::cout << "GameOverState Pause" << std::endl;
}

void GameOverState::Resume()
{
	std::cout << "GameOverState Resume" << std::endl;
}

void GameOverState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.display();
}
void GameOverState::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{

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

		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.Quit();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::I:
				m_next = StateMachine::Build<IntroState>(m_machine, m_window, true);
				LevelState::m_currentLevel = 0;
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}