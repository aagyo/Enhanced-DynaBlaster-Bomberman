#include "PlayState.h"
#include "MenuState.h"
#include "LevelState.h"
#include "GameLostState.h"
#include "Player.h"
#include "GameBar.h"

#include <memory>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include "Logger.h"

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
	globalLogger.LogData("Playing state", LogSeverity::info);

	ReadStatsFromFile();
}

void PlayState::WriteStatsInFile() {



	std::ofstream file("stats.txt");

	if (m_player.GetIsDead() == false) {

		file << m_player.GetNumberOfLives() << "\n";
		file << m_player.GetMaxNumberOfBombs() << "\n";
		file << m_player.GetPlayerSpeed() << "\n";
		file << m_player.GetRadiusStatus() << "\n";
		file << m_player.GetIsCollision() << "\n";

		file << m_bar->GetHighScore() << "\n";
	}

	file.close();

}

void PlayState::ReadStatsFromFile() {

	std::ifstream file("stats.txt");

	if (LevelState::m_currentLevel != 0) {
		std::string lineFromFile;

		file >> lineFromFile;
		m_player.SetLife(static_cast<uint16_t>(std::stoi(lineFromFile)));
		m_bar->SetLifeText(static_cast<uint16_t>(std::stoi(lineFromFile)));

		file >> lineFromFile;
		m_player.SetMaxNumberOfBombs(static_cast<uint16_t>(std::stoi(lineFromFile)));

		file >> lineFromFile;
		m_player.SetPlayerSpeed(std::stof(lineFromFile));

		file >> lineFromFile;
		m_player.SetRadius(static_cast<uint16_t>(std::stoi(lineFromFile)));

		file >> lineFromFile;
		m_player.SetIsCollision(static_cast<bool>(std::stoi(lineFromFile)));

		file >> lineFromFile;
		m_bar->SetScoreText(std::stoi(lineFromFile));
	}

	file.close();

}

void PlayState::WriteLifeInFile() {

	std::ifstream fileInput("stats.txt");
	std::stringstream buffer;
	buffer << fileInput.rdbuf();
	std::string str = buffer.str();

	str[0] = '0' + m_player.GetNumberOfLives();

	std::ofstream fileOutput("stats.txt");

	fileOutput << str;

	fileInput.close();
	fileOutput.close();
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

	m_map.GenerateRandomTeleport();
}

void PlayState::CheckForCollision()
{
	const uint16_t numberOfBlocks = 17 * 17;
	
	if (m_player.GetIsCollision() == true)
	{
		for (uint16_t blockIndex = 0; blockIndex < numberOfBlocks; blockIndex++)
		{
			const EBlockType currentBlockType = m_map.GetBlock(blockIndex).GetBlockType();

			if (currentBlockType != EBlockType::EmptyBlock && currentBlockType != EBlockType::PortalBlock && currentBlockType != EBlockType::PowerUpBlock
				&& currentBlockType != EBlockType::FireBlock && currentBlockType != EBlockType::PortalVisibleBlock)
			{
				m_map.GetBlock(blockIndex).GetCollider().CheckCollision(*&m_player.GetCollider());
			}
		}
	}
	else 
	{
		for (uint16_t blockIndex = 0; blockIndex < numberOfBlocks; blockIndex++)
		{
			const EBlockType currentBlockType = m_map.GetBlock(blockIndex).GetBlockType();

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
		m_player.AddNumberOfBombs(1);
		break;

	case PowerType::GoldBomb:
		m_player.AddNumberOfBombs(9);
		break;

	case PowerType::BlockPasser:
		m_player.SetIsCollision(false);
		break;

	case PowerType::Fire:
		m_player.AddRadius(1);
		break;

	case PowerType::GoldFire:
		m_player.AddRadius(9);
		break;

	case PowerType::Skate:
		m_player.AddPlayerSpeed(0.2f);
		break;

	case PowerType::GoldSkate:
		m_player.AddPlayerSpeed(2.0f);
		break;

	case PowerType::Clock:
		m_bar->SetAddTime(30);
		break;

	case PowerType::LifeUp:
		m_player.AddLife(1);
		m_bar->SetLifeText(m_player.GetNumberOfLives());
		break;

	case PowerType::Detonator:
		m_map.SetDetonator(true);
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
			m_map.ClearBlock(m_map.m_bombsList.front()->GetBombShape().getPosition());
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
		{
			DrawExplosion(m_map.m_bombsList[0], 0);
		}
		
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

void PlayState::VerifyEnemyDead(const Enemy* enemy)
{
	if (enemy != nullptr && m_map.IsEnemyDead(enemy) == true)
		m_bar->SetScoreText(1000);
}

bool PlayState::IsPlayerOnTeleport()
{
	const auto playerPositionIndexColumn = static_cast<uint16_t>((m_player.GetPositionX() + 24.f) / 48.f);
	const auto playerPositionIndexLine = static_cast<uint16_t>((m_player.GetPositionY() + 24.f) / 48.f);

	const uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	if (m_map.GetBlock(indexPlayer).GetBlockType() == EBlockType::PortalBlock)
	{
		return true;
	}

	return false;
}

bool PlayState::IsPlayerOnPowerUp() {

	const auto playerPositionIndexColumn = static_cast<uint16_t>((m_player.GetPositionX() + 24.f) / 48.f);
	const auto playerPositionIndexLine = static_cast<uint16_t>((m_player.GetPositionY() + 24.f) / 48.f);

	const uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

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
		return true;
	}
	
	return false;
}

void PlayState::IsPlayerOnFireBlock()
{
	const auto playerPositionIndexColumn = static_cast<uint16_t>((m_player.GetPositionX() + 24.f) / 48.f);
	const auto playerPositionIndexLine = static_cast<uint16_t>((m_player.GetPositionY() + 24.f) / 48.f);

	const uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	if (m_map.GetBlock(indexPlayer).GetBlockType() == EBlockType::FireBlock)
	{
		m_wasPlayerOnFire = true;
	}
}

bool PlayState::IsPlayerOnEnemy()
{
	bool isOnEnemy = false;
	for (auto& enemy : m_map.GetEnemy())
	{
		if (enemy != nullptr) {
			int playerPositionIndexColumn = (m_player.GetPositionX() + 24) / 48;
			int playerPositionIndexLine = (m_player.GetPositionY() + 24) / 48;

			uint16_t indexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

			int enemyPositionIndexColumn = (enemy->GetShape().getPosition().x + 24) / 48;
			int enemyPositionIndexLine = (enemy->GetShape().getPosition().y + 24) / 48;

			uint16_t indexEnemy = enemyPositionIndexLine * 17 + enemyPositionIndexColumn;

			if (indexPlayer == indexEnemy)
			{
				isOnEnemy = true;
			}
		}
	}
	return isOnEnemy;
}

void PlayState::Pause()
{
	DeleteMusicBuffer();
	m_clock.Pause();
	globalLogger.LogData("Game Paused", LogSeverity::info);
}

void PlayState::Resume()
{
	m_clock.Resume();

	m_soundBuffer = new sf::SoundBuffer;
	m_soundBuffer->loadFromFile("../_external/audio/play.flac");
	m_sound = new sf::Sound;
	m_sound->setBuffer(*m_soundBuffer);
	m_sound->play();
	globalLogger.LogData("Game Resumed", LogSeverity::info);
}

void PlayState::Update()
{
	m_clock.Resume();
	
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
			m_clock.Reset();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				if (pressed == false)
				{
					pressed = true;
					remove("Stats.txt");
					m_next = StateMachine::Build<MenuState>(m_machine, m_window, false);	
				}
				break;
				
			case sf::Keyboard::Space:
				m_map.GenerateBombs(m_player.GetPlayerShape().getPosition(), m_player.GetRadiusStatus(), m_clock.GetElapsedTime().asSeconds(), m_player.GetMaxNumberOfBombs());
				break;

			case sf::Keyboard::G:
				if (m_map.GetDetonator() == true)
				{
					m_map.DetonateAllBombs();
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

void PlayState::Draw()
{
	m_window.clear();

	const float elapsedTime = m_clock.GetElapsedTime().asSeconds();

	m_window.draw(m_map);
	m_map.SetElapsedTime(elapsedTime);
	m_bar->SetElapsedTime(elapsedTime);
	m_bar->CalculateAndCheck();

	if (m_map.IsPortalGenerate() == true && m_map.GetNumberOfMonsters() == 0)
	{
		m_map.IsPortal();
	}
	
	if (m_map.GetNumberOfBombsDisplayed() == m_player.GetMaxNumberOfBombs())
	{
		m_player.SetCanPlaceBomb(false);
	}

	CreateExplosions();

	IsPlayerOnFireBlock();
	
	if (IsTimeZero() || m_wasPlayerOnFire == true || IsPlayerOnEnemy() == true)
	{
		m_player.DeadAnimation(m_clock.GetElapsedTime().asSeconds());
		m_window.draw(m_player.GetPlayerShape());
		
		if (m_player.GetIsDead() == true)
		{
			m_player.TakeLife();
			WriteLifeInFile();
			if (m_player.GetNumberOfLives() != 0)
				m_next = StateMachine::Build<LevelState>(m_machine, m_window, false);
		}
	}
	else
	{
		m_window.draw(m_player.GetPlayerShape());
		m_player.MovePlayer(elapsedTime);
		if (!m_map.m_bombsList.empty())
			m_map.CreateBombsCollision(m_player.GetPlayerShape().getPosition());
		m_map.MoveEnemy();
		for (auto& enemy : m_map.GetEnemy())
		{
			VerifyEnemyDead(enemy);
		}
		CheckForCollision();
	}

	if (IsPlayerOnPowerUp() == true) 
	{
		StatusUpdate(m_map.GetPower()->GetPowerType());
		m_map.RemovePowerUp();
		m_map.ClearBlock(m_player.GetPlayerShape().getPosition());
	}

	if (IsPlayerOnTeleport())
	{
		WriteStatsInFile();
		LevelState::m_currentLevel++;
		m_next = StateMachine::Build<LevelState>(m_machine, m_window, false);
	}

	if (m_player.GetNumberOfLives() == 0)
	{
		remove("stats.txt");
		m_next = StateMachine::Build<GameLostState>(m_machine, m_window, false);
	}

	m_window.draw(*m_bar);
	m_window.display();
}