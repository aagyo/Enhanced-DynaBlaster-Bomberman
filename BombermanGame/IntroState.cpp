#include "IntroState.h"
#include "LevelState.h"
#include "StateMachine.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	window.setKeyRepeatEnabled(false);
	m_bgTexture.loadFromFile("../_external/states/introstate.png");
	m_bg.setTexture(m_bgTexture, true);

	m_soundBuffer = new sf::SoundBuffer;
	m_soundBuffer->loadFromFile("../_external/audio/intro.flac");

	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_soundBuffer);

	m_sound->play();

	std::cout << "IntroState Ctor" << std::endl;
}

void IntroState::Update()
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
				view.setViewport(sf::FloatRect(0.f, 0.f, 816, 864));
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
			break;

		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Enter:
				if (pressed == false) {

					pressed = true;
					DeleteMusicBuffer();
					m_next = StateMachine::Build<LevelState>(m_machine, m_window, true);

				}
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
	m_window.display();
}

void IntroState::DeleteMusicBuffer()
{
	m_sound->~Sound();
	m_soundBuffer->~SoundBuffer();
}
