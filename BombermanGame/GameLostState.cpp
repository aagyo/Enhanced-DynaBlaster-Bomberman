#include "GameLostState.h"
#include "IntroState.h"
#include "LevelState.h"

#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

GameLostState::GameLostState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	m_bgTexture.loadFromFile("../_external/states/gameloststate.png");
	m_bg.setTexture(m_bgTexture, true);

	m_soundBuffer.loadFromFile("../_external/audio/gamelost.flac");
	m_sound.setBuffer(m_soundBuffer);
	m_sound.play();
	m_sound.setLoop(true);
}
void GameLostState::Pause()
{
	// empty
}

void GameLostState::Resume()
{
	// empty
}

void GameLostState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.display();
}

void GameLostState::Update()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{

		if (event.type == sf::Event::Resized)
		{
			const auto windowWidth = static_cast<float>(event.size.width);
			const auto windowHeight = static_cast<float>(event.size.height);

			const float newWidth = windowHeight;
			const float newHeight = windowWidth;
			const float offset_width = (windowWidth - newWidth) / 2.0f;
			const float offset_height = (windowHeight - newHeight) / 2.0f;

			sf::View view = m_window.getDefaultView();

			if (windowWidth < m_windowSize || windowHeight < m_windowSize)
			{
				view.setViewport(sf::FloatRect(0.f, 0.f, m_windowSize, m_windowSize));
				m_window.setSize(sf::Vector2u(static_cast<uint16_t>(m_windowSize), static_cast<uint16_t>(m_windowSize)));
				m_window.setPosition(sf::Vector2i(400, 200));
			}
			else
			{
				if (windowWidth >= windowHeight)
				{
					view.setViewport(sf::FloatRect(offset_width / windowWidth, 0.0, newWidth / windowWidth, 1.0));
				}
				else
				{
					view.setViewport(sf::FloatRect(0.0, offset_height / windowHeight, 1.0, newHeight / windowHeight));
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
				LevelState::m_currentLevel = 0;
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
}