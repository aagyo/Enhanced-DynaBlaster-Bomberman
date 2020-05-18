#include "IntroState.h"
#include "LevelState.h"
#include "StateMachine.h"

#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include "Logger.h"

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	window.setKeyRepeatEnabled(false);
	m_bgTexture.loadFromFile("../_external/states/introstate.png");
	m_bg.setTexture(m_bgTexture, true);

	m_soundBuffer = new sf::SoundBuffer;
	m_soundBuffer->loadFromFile("../_external/audio/intro.flac");

	globalLogger.LogData("Intro State", LogSeverity::info);
	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_soundBuffer);
	m_sound->play();
}

void IntroState::Update()
{
	sf::Event event;
	
	bool pressed = false;

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
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Enter:
				if (pressed == false) 
				{
					pressed = true;
					DeleteMusicBuffer();
					m_next = StateMachine::Build<LevelState>(m_machine, m_window, true);
				}
				break;

			case sf::Keyboard::Escape:
				globalLogger.LogData("**************GAME CLOSED****************");
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
	// empty
}

void IntroState::Resume()
{
	// empty
}

void IntroState::DeleteMusicBuffer()
{
	m_sound->~Sound();
	m_soundBuffer->~SoundBuffer();
}

void IntroState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.display();
}