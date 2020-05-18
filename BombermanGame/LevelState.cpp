#include "IntroState.h"
#include "LevelState.h"
#include "PlayState.h"
#include "GameOverState.h"

#include <fstream>
#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include "Logger.h"

uint16_t LevelState::m_currentLevel = 0;

LevelState::LevelState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	if (m_levels.empty())
	{
		{
			std::ifstream inputLevels("../_external/levels/levels.txt");
			std::string level;

			while (std::getline(inputLevels, level))
			{
				m_levels.push_back(level);
			}
		}
	}

	if (m_currentLevel == m_levels.size())
	{
		m_next = StateMachine::Build<GameOverState>(m_machine, m_window, true);
	}
	else
	{
		m_bgTexture.loadFromFile("../_external/states/levelstate.png");
		m_bg.setTexture(m_bgTexture, true);

		m_font.loadFromFile("../_external/font/bm.ttf");
		m_text.setString(m_levels[m_currentLevel]);
		m_text.setFont(m_font);
		m_text.setCharacterSize(80);
		m_text.setPosition(200.f, 325.f);

		m_soundBuffer = new sf::SoundBuffer;
		m_soundBuffer->loadFromFile("../_external/audio/level.flac");

		m_sound = new sf::Sound;
		m_sound->setBuffer(*m_soundBuffer);
		m_sound->play();

		globalLogger.LogData("LevelState", LogSeverity::info);
		globalLogger.LogData("New Level:", LogSeverity::info);
		globalLogger.LogData(m_currentLevel, LogSeverity::info);
	}
}

void LevelState::Pause()
{
	// empty
}

void LevelState::Resume()
{
	// empty
}

void LevelState::Draw()
{
	m_window.clear();
	m_window.draw(m_bg);
	m_window.draw(m_text);
	m_window.display();
}

void LevelState::DeleteMusicBuffer()
{
	m_soundBuffer->~SoundBuffer();
	m_sound->~Sound();
}

void LevelState::Update()
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
			switch (event.key.code)
			{
			case sf::Keyboard::C:
				if (pressed == false)
				{
					pressed = true;
					DeleteMusicBuffer();
					m_next = StateMachine::Build<PlayState>(m_machine, m_window, true);
				}
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