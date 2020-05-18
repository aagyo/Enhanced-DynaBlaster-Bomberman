#include "Window.h"
#include "Bomb.h"
#include <SFML/Graphics.hpp>
#include <math.h>

Window::Window()
{
	m_map.CreateTilesOnMap(sf::Vector2u(48, 48));
}

void Window::CheckForCollision()
{
	uint32_t numberOfBlocks = 289;

	for (uint16_t index = 0; index < numberOfBlocks; index++)
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
	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "DynaBlaster Bomberman. Made by PixBomb!");
	uint16_t bombRadius = 2;
	bool spacePressed = false;
	bool explosionCreated;

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

		Bomb bomb(m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionX() / 48))).GetPosition().x,
			m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionY() / 48))).GetPosition().x,
			bombRadius, m_clock.GetElapsedTime().asSeconds());


		if (m_player.GetCanPlaceBomb() == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			explosionCreated = false;
			DestroyBlocks d(*&m_player.GetPlayerShape(), m_map.m_map, m_map.m_blocks);
			d.ChangeBlocks();

			m_bomb = bomb;
			m_window.draw(m_bomb.GetBombShape());
			m_player.SetCanPlaceBomb(false);
			spacePressed = true;
		}
		else if(spacePressed == true)
		{
			if (m_bomb.GetBombStatus() == false && m_bomb.GetExplosionRadius() != 0)
			{
				m_bomb.Update(m_clock.GetElapsedTime().asSeconds());
				m_window.draw(m_bomb.GetBombShape());
			}
			else
			{
				if (explosionCreated == false)
				{
					m_explosion = new Explosion(m_bomb.GetBombShape().getPosition(), m_bomb.GetExplosionRadius(), m_map);
					m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
					explosionCreated = true;
				}
				else
				{
					m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
					explosionCreated = m_explosion->GetExplosionState();
					if (explosionCreated == false)
					{
						m_player.SetCanPlaceBomb(true);
						spacePressed = false;
					}
				}
			}
		}
		m_window.draw(m_player.GetPlayerShape());
		m_player.MovePlayer();
		CheckForCollision();

		m_window.display();
	}
}