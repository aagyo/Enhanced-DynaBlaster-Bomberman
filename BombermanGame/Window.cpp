#include "Window.h"
#include "Bomb.h"
#include <SFML/Graphics.hpp>
#include <math.h>


Window::Window()
{
	m_map.CreateTilesOnMap(sf::Vector2u(48, 48));
}

void Window::CheckForCollision() {

	for (uint16_t index = 0; index < 289; index++)
	{
		EBlockType currentBlockType = m_map.GetBlock(index).GetBlockType();

		if (currentBlockType != EBlockType::EmptyBlock)
		{
			m_map.GetBlock(index).GetCollider().CheckCollision(*&m_player.GetCollider());
		}
	}
}

sf::Time Window::GetElapsedTime() const
{
	return m_clock.GetElapsedTime();
}

void Window::ShowWindow()
{
	float time;
	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "DynaBlaster Bomberman made by PixBomb");
	while (m_window.isOpen())
	{
		m_clock.Resume();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				m_clock.Reset();
				break;
			}
		}
		m_window.clear();
		m_window.draw(m_map);

		Bomb bomb(m_map.GetBlock(round(m_player.GetPositionX() / 48)).GetPosition().y, m_map.GetBlock(round(m_player.GetPositionY() / 48)).GetPosition().y, 2, m_clock.GetElapsedTime().asSeconds());

		if (m_player.GetCanPlaceBomb() == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			m_bomb = bomb;
			m_window.draw(m_bomb.GetBombShape());
			m_player.SetCanPlaceBomb(false);
		}
		else
		{
			if (m_bomb.GetBombStatus() == false && m_bomb.GetExplosionRadius() != 0)
			{
				m_bomb.Update(m_clock.GetElapsedTime().asSeconds());
				m_window.draw(m_bomb.GetBombShape());
			}
			else
				m_player.SetCanPlaceBomb(true);
		}

		m_window.draw(m_player.GetPlayerShape());
		m_player.MovePlayer();
		CheckForCollision();

		m_window.display();
	}

}
