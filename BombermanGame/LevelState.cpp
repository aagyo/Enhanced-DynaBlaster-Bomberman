#include "IntroState.h"
#include "LevelState.h"
#include "PlayState.h"
#include "GameOverState.h"

#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>

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

		std::cout << "LevelState Ctor" << std::endl;
	}
}

void LevelState::Pause()
{
	std::cout << "LevelState Pause" << std::endl;
}

void LevelState::Resume()
{
	std::cout << "LevelState Resume" << std::endl;
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
			auto window_width = event.size.width;
			auto window_height = event.size.height;

			float new_width = window_height;
			float new_height = window_width;
			float offset_width = (window_width - new_width) / 2.0;
			float offset_height = (window_height - new_height) / 2.0;

			sf::View view = m_window.getDefaultView();

			if (window_width < 816 || window_height < 864)
			{
				view.setViewport(sf::FloatRect(0.f, 0.f, 864, 864));
				m_window.setSize(sf::Vector2u(864, 864));
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
			m_currentLevel = 0;
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
					m_currentLevel++;
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