#include "PlayState.h"
#include "MenuState.h"
#include "LevelState.h"
#include "GameOverState.h"
#include "GameLostState.h"
#include "Player.h"
#include "Gamebar.h"

#include <memory>
#include <SFML/Graphics.hpp>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace) :
	State(machine, window, replace)
{
	CreateMap();
	m_bar = new GameBar();

	m_soundBuffer = new sf::SoundBuffer;
	m_soundBuffer->loadFromFile("../_external/audio/play.flac");

	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_soundBuffer);

	m_sound->play();

	std::cout << "PlayState Ctor" << std::endl;
}

void PlayState::DeleteMusicBuffer()
{
	m_sound->~Sound();
	m_soundBuffer->~SoundBuffer();
}

void PlayState::CreateMap()
{
	const uint16_t tileSize = 48;

	m_map.CreateTilesOnMap(sf::Vector2u(tileSize, tileSize));
}

void PlayState::CheckForCollision()
{
	const uint32_t numberOfBlocks = 289;
	if (m_player.GetIsCollision() == true) {
		for (uint16_t blockIndex = 0; blockIndex < numberOfBlocks; blockIndex++)
		{
			EBlockType currentBlockType = m_map.GetBlock(blockIndex).GetBlockType();

			if (currentBlockType != EBlockType::EmptyBlock && currentBlockType != EBlockType::PortalBlock && currentBlockType != EBlockType::PowerUpBlock
				&& currentBlockType != EBlockType::FireBlock)
			{
				m_map.GetBlock(blockIndex).GetCollider().CheckCollision(*&m_player.GetCollider());
			}
		}
	}
	else {

		for (uint16_t blockIndex = 0; blockIndex < numberOfBlocks; blockIndex++)
		{
			EBlockType currentBlockType = m_map.GetBlock(blockIndex).GetBlockType();

			if (currentBlockType != EBlockType::EmptyBlock && currentBlockType != EBlockType::PortalBlock && currentBlockType != EBlockType::PowerUpBlock
				&& currentBlockType != EBlockType::FireBlock && currentBlockType != EBlockType::StoneBlock)
			{
				m_map.GetBlock(blockIndex).GetCollider().CheckCollision(*&m_player.GetCollider());
			}
		}
	}
}

void PlayState::StatusUpdate(const PowerType& powerUp)
{
	switch (powerUp)
	{
	case PowerType::BombUp:
		m_player.SetNumberOfBombs(1);
		break;

	case PowerType::GoldBomb:
		m_player.SetNumberOfBombs(9);
		break;

	case PowerType::BlockPasser:
		m_player.SetIsCollision(false);
		break;

	case PowerType::Fire:
		m_player.SetRadius(1);
		break;

	case PowerType::GoldFire:
		m_player.SetRadius(9);
		break;

	case PowerType::Skate:
		m_player.SetPlayerSpeed(3.0f);
		break;

	case PowerType::GoldSkate:
		m_player.SetPlayerSpeed(3.0f);
		break;

	case PowerType::Clock:
		m_bar->SetAddTime(30);
		break;

	case PowerType::LifeUp:
		m_player.SetLife(1);
		m_bar->SetLifeText(m_player.GetNumberOfLives());
		break;

	default:
		break;
	}
}

sf::Time PlayState::GetElapsedTime() const
{
	return m_clock.GetElapsedTime();
}

void PlayState::DrawExplosion(Bomb* thisBomb, uint16_t thisIndex)
{
	if (thisBomb->GetExplosionShow() == false)
	{
		m_explosionsList[thisIndex]->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
		thisBomb->SetExplosionShow(true);
	}
	else
	{
		m_explosionsList[thisIndex]->Update(m_clock.GetElapsedTime().asSeconds(), m_window);
		thisBomb->SetExplosionShow(m_explosionsList[thisIndex]->GetExplosionState());

		if (thisBomb->GetExplosionShow() == false)
		{
			m_explosionsList.erase(m_explosionsList.begin());
			m_map.m_bombsList.erase(m_map.m_bombsList.begin());
			m_map.ClearFireBlocks();
			m_player.SetCanPlaceBomb(true);
		}
	}
}

void PlayState::CreateExplosions()
{
	if (!m_map.m_bombsList.empty() && m_explosionsList.size() != m_map.m_bombsList.size())
	{
		InsertExplosion(m_map.m_bombsList[m_map.m_bombsList.size() - 1]);
	}
	if (!m_map.m_bombsList.empty())
	{
		if (m_map.m_bombsList.front()->GetBombStatus() == true)
			DrawExplosion(m_map.m_bombsList[0], 0);
		if (m_map.m_bombsList.size() > 1)
		{
			for (uint16_t index = 1; index < m_map.m_bombsList.size(); index++)
			{
				m_map.EarlyExplode(m_map.m_bombsList[index]);
				if (m_map.m_bombsList[index]->GetBombStatus() == true)
				{
					DrawExplosion(m_map.m_bombsList[index], index);
				}
			}
		}
	}
}

void PlayState::InsertExplosion(Bomb* thisBomb)
{
	m_explosionsList.push_back(new Explosion(thisBomb->GetBombShape().getPosition(), thisBomb->GetExplosionRadius(), &m_map));
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

	if (m_map.GetBlock(indexPlayer).GetBlockType() == EBlockType::PowerUpBlock)
	{
		return true;
	}

	return false;
}

bool PlayState::IsTimeZero()
{
	if (m_bar->GetTimeFinished() == true)
	{
		m_player.SetLife(-1);
		return true;
	}
	return false;
}

void PlayState::IsPlayerOnFireBlock()
{
	int playerPositionIndexColumn = (m_player.GetPositionX() + 24) / 48;
	int playerPositionIndexLine = (m_player.GetPositionY() + 24) / 48;

	uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	if (m_map.GetBlock(indexPlayer).GetBlockType() == EBlockType::FireBlock)
	{
		m_wasPlayerOnFire = true;
	}
}

void PlayState::Pause()
{

	DeleteMusicBuffer();


	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::Resume()
{
	m_clock.Resume();

	m_soundBuffer = new sf::SoundBuffer;
	m_soundBuffer->loadFromFile("../_external/audio/play.flac");

	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_soundBuffer);

	m_sound->play();

	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::Update()
{
	sf::Event event;
	m_clock.Resume();
	bool pressed = false;

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
			m_clock.Reset();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				if (pressed == false)
				{
					pressed = true;
					m_next = StateMachine::Build<MenuState>(m_machine, m_window, false);	
				}
				break;
			case sf::Keyboard::Space:
				m_map.GenerateBombs(m_player.GetPlayerShape().getPosition(), m_player.GetRadiusStatus(), m_clock.GetElapsedTime().asSeconds(), m_player.GetMaxNoBombs());
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

	float elapsedTime = m_clock.GetElapsedTime().asSeconds();

	m_window.draw(m_map);
	m_map.SetElapsedTime(elapsedTime);
	m_bar->SetElapsedTime(elapsedTime);
	m_bar->CalculateAndCheck();

	m_bar->SetScoreText(1);

	if (m_map.GetNoBombsDisplayed() == m_player.GetMaxNoBombs())
		m_player.SetCanPlaceBomb(false);

	CreateExplosions();

	IsPlayerOnFireBlock();
	if (IsTimeZero() || m_wasPlayerOnFire == true)
	{
		m_player.DeadAnimation(m_clock.GetElapsedTime().asSeconds());
		m_window.draw(m_player.GetPlayerShape());
		if (m_player.GetIsDead() == true)
		{
			LevelState::m_currentLevel--;
			m_next = StateMachine::Build<LevelState>(m_machine, m_window, false);
		}
	}
	else
	{
		m_window.draw(m_player.GetPlayerShape());
		m_player.MovePlayer(elapsedTime);
		CheckForCollision();
	}

	if (IsPlayerOnPowerUp() == true) {
		StatusUpdate(m_map.GetPower()->GetPowerType());
		m_map.RemovePowerUp();
		m_map.ClearBlock(m_player.GetPlayerShape().getPosition());
		std::cout << "sters" << "\n";
	}
	 //MODIFICA AICI

	if (IsPlayerOnTeleport())
	{
		m_next = StateMachine::Build<LevelState>(m_machine, m_window, false);
		
	}

	if (m_player.GetNumberOfLives() == 0)
	{
		m_next = StateMachine::Build<GameLostState>(m_machine, m_window, false);
	}

	m_window.draw(*m_bar);
	m_window.display();
}