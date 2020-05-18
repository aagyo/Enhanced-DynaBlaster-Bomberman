#include "PlayState.h"
#include "MenuState.h"
#include "LevelState.h"
#include "GameOverState.h"
#include "GameLostState.h"
#include "Player.h"

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	CreateMap();

	m_soundBuffer.loadFromFile("../_external/audio/play.flac");
	m_sound.setBuffer(m_soundBuffer);
	m_sound.play();
	m_sound.setLoop(true);

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

		if (currentBlockType != EBlockType::EmptyBlock && currentBlockType != EBlockType::PortalBlock && currentBlockType != EBlockType::PowerUpBlock)
		{
			m_map.GetBlock(blockIndex).GetCollider().CheckCollision(*&m_player.GetCollider());
		}
	}
}

sf::Time PlayState::GetElapsedTime() const
{
	return m_clock.GetElapsedTime();
}

void PlayState::DrawExplosion(Bomb* thisBomb)
{
	if (thisBomb->GetExplosionShow() == false)
	{
		m_explosion = new Explosion(thisBomb->GetBombShape().getPosition(), thisBomb->GetExplosionRadius(), &m_map);
		m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
		thisBomb->SetExplosionShow(true);
	}
	else
	{
		m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
		thisBomb->SetExplosionShow(m_explosion->GetExplosionState());

		if (thisBomb->GetExplosionShow() == false)
		{
			m_map.m_bombsQueue.erase(m_map.m_bombsQueue.begin());
			delete m_explosion;
		}
	}
}

bool PlayState::IsPlayerOnTeleport()
{

	int playerPositionIndexColumn = (m_player.GetPositionX() + 24) / 48;
	int playerPositionIndexLine = (m_player.GetPositionY() + 24) / 48;

	uint16_t IndexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	if (m_map.GetBlock(IndexPlayer).GetBlockType() == EBlockType::PortalBlock)
	{
		return true;
	}

	return false;
}

bool PlayState::IsPlayerOnPowerUp() {

	int playerPositionIndexColumn = (m_player.GetPositionX() + 24) / 48;
	int playerPositionIndexLine = (m_player.GetPositionY() + 24) / 48;

	uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;


	std::cout << indexPlayer << "\n";

	if (m_map.GetBlock(indexPlayer).GetBlockType() == EBlockType::PowerUpBlock)
	{
		return true;
	}

	return false;
}

void PlayState::Pause()
{
	m_clock.Pause();
	m_sound.pause();
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::Resume()
{
	m_clock.Resume();
	m_sound.play();
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::Update()
{
	sf::Event event;
	m_clock.Resume();

	while (m_window.pollEvent(event))
	{

		if (event.type == sf::Event::Resized)
		{
			auto window_width = event.size.width;
			auto window_height = event.size.height;

			float new_width = window_height;
			float new_height = window_width;
			float offset_width = static_cast<float>(window_width - new_width) / 2.0;
			float offset_height = static_cast<float>(window_height - new_height) / 2.0;

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
			m_clock.Reset();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				m_next = StateMachine::Build<MenuState>(m_machine, m_window, false);
				break;
			case sf::Keyboard::Space:
				m_map.GenerateBombs(m_player.GetPlayerShape().getPosition(), bombRadius, m_clock.GetElapsedTime().asSeconds(), m_player.GetMaxNoBombs());
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
	m_map.SetElapsedTime(m_clock.GetElapsedTime().asSeconds());


	//if (m_player.GetCanPlaceBomb() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	//{
	///*	m_bomb = new Bomb(m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionX() / 48))).GetPosition().x,
	//		m_map.GetBlock(static_cast<uint16_t>(round(m_player.GetPositionY() / 48))).GetPosition().x,
	//		bombRadius, m_clock.GetElapsedTime().asSeconds());
	//	m_window.draw(m_bomb->GetBombShape());*/
	//	m_map.GenerateBombs(m_player.GetPlayerShape().getPosition(), bombRadius, m_clock.GetElapsedTime().asSeconds(),m_player.GetMaxNoBombs());
	//}

	if (m_map.GetNoBombsDisplayed() == m_player.GetMaxNoBombs())
		m_player.SetCanPlaceBomb(false);

	if (!m_map.m_bombsQueue.empty() && m_map.m_bombsQueue.front()->GetBombStatus() == true)
	{
		DrawExplosion(m_map.m_bombsQueue.front());
		m_player.SetCanPlaceBomb(true);
	}
	//else if (m_player.GetCanPlaceBomb() == false)
	//{
	//	if (!m_bomb->GetBombStatus() && m_bomb->GetExplosionRadius() != 0)
	//	{
	//		m_window.draw(m_bomb->GetBombShape());
	//		m_bomb->Update(m_clock.GetElapsedTime().asSeconds());
	//	}
	//	else
	//	{
	//		if (m_bomb->GetExplosionShow() == false)
	//		{
	//			m_explosion = new Explosion(m_bomb->GetBombShape().getPosition(), m_bomb->GetExplosionRadius(), &m_map);
	//			m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
	//			m_bomb->SetExplosionShow(true);
	//		}
	//		else
	//		{
	//			m_explosion->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
	//			m_bomb->SetExplosionShow(m_explosion->GetExplosionState());

	//			if (m_bomb->GetExplosionShow() == false)
	//			{
	//				//ChangeBlocks();
	//				m_player.SetCanPlaceBomb(true);
	//				delete m_explosion;
	//				delete m_bomb;
	//			}
	//		}
	//	}
	//}
	m_window.draw(m_player.GetPlayerShape());
	m_player.MovePlayer(m_clock.GetElapsedTime().asSeconds());
	CheckForCollision();

	if (IsPlayerOnPowerUp() == true) {
		m_map.RemovePowerUp();
		m_map.ClearBlock(m_player.GetPlayerShape().getPosition());
		std::cout << "sters" << "\n";
	}


	// MODIFICA AICI

	if (IsPlayerOnTeleport())
	{
		m_next = StateMachine::Build<LevelState>(m_machine, m_window, false);
	}

	if (Player::GetNumberOfLives() == 0)
	{
		m_next = StateMachine::Build<GameLostState>(m_machine, m_window, false);
	}

	m_window.display();
}