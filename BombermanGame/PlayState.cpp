#include "PlayState.h"
#include "MenuState.h"
#include "DestroyBlocks.h"
#include "Map.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	CreateMap();
	std::cout << "PlayState Ctor" << std::endl;
}

void PlayState::CreateMap()
{
	const uint16_t tileSize = 48;

	m_map.CreateTilesOnMap(sf::Vector2u(tileSize, tileSize));
}

void PlayState::CheckForCollision()
{
	const uint32_t numberOfBlocks = 289;

	for (uint16_t blockIndex = 0; blockIndex < numberOfBlocks; blockIndex++)
	{
		EBlockType currentBlockType = m_map.GetBlock(blockIndex).GetBlockType();

		if (currentBlockType != EBlockType::EmptyBlock)
		{
			m_map.GetBlock(blockIndex).GetCollider().CheckCollision(*&m_player.GetCollider());
		}
	}
}

sf::Time PlayState::GetElapsedTime() const
{
	return m_clock.GetElapsedTime();
}

void PlayState::Pause()
{
	m_clock.Pause();
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::Resume()
{
	m_clock.Resume();
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::Update()
{
	m_clock.Resume();

	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_machine.Quit();
			m_clock.Reset();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				m_next = StateMachine::Build<MenuState>(m_machine, m_window, false);
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

void PlayState::Draw()
{
	m_window.clear();
	m_window.draw(m_map);

	m_deltaTime = m_clock.GetElapsedTime().asSeconds();

	DestroyBlocks destoryBlocks(*&m_player.GetPlayerShape(), *&m_map.m_map, *&m_map.m_blocks, *&m_map.m_tileTexture);

	const uint16_t bombRadius = 2;
	Bomb bomb(m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionX() / 48))).GetPosition().x,
		m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionY() / 48))).GetPosition().x,
		bombRadius, m_clock.GetElapsedTime().asSeconds());

	if (m_player.GetCanPlaceBomb() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		m_bomb = bomb;
		m_window.draw(m_bomb.GetBombShape());
		destoryBlocks.ChangeBlocks();
		m_player.SetCanPlaceBomb(false);
	}
	else
	{
		if (!m_bomb.GetBombStatus() && m_bomb.GetExplosionRadius() != 0)
		{
			m_window.draw(m_bomb.GetBombShape());
			m_bomb.Update(m_clock.GetElapsedTime().asSeconds());
		}
		else
		{
			m_player.SetCanPlaceBomb(true);
		}
	}

	m_window.draw(m_player.GetPlayerShape());
	m_player.MovePlayer(m_deltaTime);
	CheckForCollision();

	m_window.display();
}