#include "Map.h"
#include "PlayState.h"
#include "LevelState.h"
#include <random>

void Map::CreateTilesOnMap(const sf::Vector2u& tileSize)
{
	uint16_t tileNumber = 0;

	GenerateMapLayout();
	ChangeStageTexture();

	for (uint16_t heightIndex = 0; heightIndex < m_mapHeight; heightIndex++)
	{
		for (uint16_t widthIndex = 0; widthIndex < m_mapWidth; widthIndex++)
		{
			const auto tileNumberIndex = static_cast<uint16_t>(m_map[tileNumber]);
			const uint16_t textureLineIndex = tileNumberIndex % (m_tileset.getSize().x / tileSize.x);
			const uint16_t textureColumnIndex = tileNumberIndex / (m_tileset.getSize().x / tileSize.x);

			m_blocks[tileNumber].SetPosition(sf::Vector2f(static_cast<float>(widthIndex)* tileSize.x, static_cast<float>(heightIndex)* tileSize.y));
			m_blocks[tileNumber].SetBlockType(m_map[tileNumber]);
			m_blocks[tileNumber].SetBlockTexture(&m_tileset, sf::IntRect(textureLineIndex * tileSize.x, textureColumnIndex * tileSize.y, tileSize.x, tileSize.y));

			tileNumber++;
		}
	}

	GenerateRandomEnemy();
}

Block& Map::GetBlock(uint16_t position)
{
	return m_blocks[position];
}

uint16_t Map::GetWidth()
{
	return m_mapWidth;
}

uint16_t Map::GetHeight()
{
	return m_mapHeight;
}

bool Map::GenerateDestroyableBlock()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<> dis(0, 1);
	return dis(gen);
}

void Map::ChangeStageTexture()
{
	m_tileset.loadFromFile("../_external/sprites/stage" + std::to_string((LevelState::m_currentLevel / 8 + 1)) + ".png");
	m_tileset.setSmooth(true);
}

void Map::GenerateBombs(const sf::Vector2f& playersPosition, const uint16_t bombRadius, const float timeElapsed, const uint16_t maxNoBombs)
{
	if (m_bombsList.size() < maxNoBombs)
	{
		if (CheckBombsPositions(playersPosition) == true)
		{
			Bomb* newBomb = new Bomb(m_blocks[static_cast<uint16_t>(round(playersPosition.x / m_tileSize))].GetPosition().x,
				m_blocks[static_cast<uint16_t>(round(playersPosition.y / m_tileSize))].GetPosition().x,
				bombRadius, timeElapsed);
			m_bombsList.push_back(newBomb);
		}
	}
}

uint16_t Map::GetNumberOfBombsDisplayed() const
{
	return static_cast<uint16_t>(m_bombsList.size());
}

void Map::GenerateRandomTeleport()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<> dis(0, m_blocks.size() - 1);

	uint16_t randomIndex = 0;

	while (m_blocks[randomIndex].IsPortal() != true)
	{
		randomIndex = dis(gen);

		if (m_map[randomIndex] == EBlockType::StoneBlock)
		{
			m_blocks[randomIndex].SetIsPortal(true);
			m_portal = new Portal(sf::Vector2f(m_blocks[randomIndex].GetBlockBody().getPosition()));
			m_portalIndex = randomIndex;
			m_portalGenerated = true;
		}
	}
}

bool Map::IsPortalGenerate()
{
	return m_portalGenerated;
}

void Map::IsPortal()
{
	m_blocks[m_portalIndex].SetBlockType(EBlockType::PortalBlock);
}

void Map::GenerateRandomPowerUp(const sf::Vector2f& position)
{
	m_powerUp = new PowerUp(sf::Vector2f(position));
	m_powerUp->CreateRandomPowerUp();
}

void Map::CreateEnemies()
{
	uint8_t maxNumberOfMobs = 8;
	uint8_t numberOfEnemys = LevelState::m_currentLevel % maxNumberOfMobs + 1;

	for (uint8_t currentLevel = 1; currentLevel <= numberOfEnemys; currentLevel++)
		if ((currentLevel + 1) % 2 == 0) {
			m_enemiesList.push_back(new Enemy());
			m_numberOfMonsters++;
		}
}

void Map::GenerateRandomEnemy() {

	const uint16_t beginIndexMap = 19;
	const uint16_t endIndexMap = m_blocks.size() - 19;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(beginIndexMap, endIndexMap);

	uint16_t randomIndex = 0;
	CreateEnemies();

	for (auto& enemy : m_enemiesList) {
		while (true)
		{
			randomIndex = dis(gen);

			if (m_map[randomIndex] == EBlockType::EmptyBlock) {
				enemy->SetPosition(m_blocks[randomIndex].GetPosition());
				break;
			}
		}
	}
}

bool Map::CheckBombsPositions(sf::Vector2f playerPosition)
{
	bool flag = false;

	if (m_bombsList.empty())
	{
		flag = true;
	}
	else
	{
		std::vector<uint16_t> bombsPositions;

		for (auto& bomb : m_bombsList)
		{
			const auto bombIndexColumn = static_cast<uint16_t>((bomb->GetBombShape().getPosition().x + (m_tileSize / 2.f)) / m_tileSize);
			const auto bombIndexLine = static_cast<uint16_t>((bomb->GetBombShape().getPosition().y + (m_tileSize / 2.f)) / m_tileSize);

			const uint16_t bombsIndex = bombIndexLine * 17 + bombIndexColumn;
			bombsPositions.push_back(bombsIndex);
		}

		const auto playerIndexColumn = static_cast<uint16_t>((playerPosition.x + (m_tileSize / 2.f)) / m_tileSize);
		const auto playerIndexLine = static_cast<uint16_t>((playerPosition.y + (m_tileSize / 2.f)) / m_tileSize);

		const uint16_t playersIndex = playerIndexLine * 17 + playerIndexColumn;

		if (std::find(bombsPositions.begin(), bombsPositions.end(), playersIndex) != bombsPositions.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return flag;
}

void Map::EarlyExplode(Bomb* bomb)
{
	const auto bombIndexColumn = static_cast<uint16_t>((bomb->GetBombShape().getPosition().x + (m_tileSize / 2.f)) / m_tileSize);
	const auto bombIndexLine = static_cast<uint16_t>((bomb->GetBombShape().getPosition().y + (m_tileSize / 2.f)) / m_tileSize);
	const auto blockIndex = bombIndexLine * 17 + bombIndexColumn;

	if (m_blocks[blockIndex].GetBlockType() == EBlockType::FireBlock)
	{
		bomb->SetBombStatus(true);
	}
}

void Map::ClearFireBlocks()
{
	for (auto& fireBlock : fireBlocks)
	{
		m_blocks[fireBlock].SetBlockType(EBlockType::EmptyBlock);
	}
}

void Map::MoveEnemy()
{
	for (auto& enemy : m_enemiesList)
	{
		if (enemy != nullptr) {

			uint16_t enemyIndexColumn = (enemy->GetShape().getPosition().x + 24) / 48;
			uint16_t enemyIndexLine = (enemy->GetShape().getPosition().y + 24) / 48;

			uint16_t index = enemyIndexLine * 17 + enemyIndexColumn;

			if (m_elapsedTime - enemy->GetLastTimeMoving() >= 0.8f)
			{

				if (enemy->GetDirection() == Direction::DOWN && enemy->GetWallHitted() == false)
					if (m_blocks[index + 17].GetBlockType() == EBlockType::EmptyBlock)
					{
						enemy->SetPosition(m_blocks[index + 17].GetPosition());
						enemy->SetLastTimeMoving(m_elapsedTime);
						enemy->SetLastDirection(enemy->GetDirection());
					}
					else
					{
						enemy->SetWallHitted(true);
					}

				if (enemy->GetDirection() == Direction::UP && enemy->GetWallHitted() == false)
					if (m_blocks[index - 17].GetBlockType() == EBlockType::EmptyBlock)
					{
						enemy->SetPosition(m_blocks[index - 17].GetPosition());
						enemy->SetLastTimeMoving(m_elapsedTime);
						enemy->SetLastDirection(enemy->GetDirection());
					}
					else
					{
						enemy->SetWallHitted(true);
					}

				if (enemy->GetDirection() == Direction::LEFT && enemy->GetWallHitted() == false)
					if (m_blocks[index - 1].GetBlockType() == EBlockType::EmptyBlock)
					{
						enemy->SetPosition(m_blocks[index - 1].GetPosition());
						enemy->SetLastTimeMoving(m_elapsedTime);
						enemy->SetLastDirection(enemy->GetDirection());
					}
					else
					{
						enemy->SetWallHitted(true);
					}

				if (enemy->GetDirection() == Direction::RIGHT && enemy->GetWallHitted() == false)
					if (m_blocks[index + 1].GetBlockType() == EBlockType::EmptyBlock)
					{
						enemy->SetPosition(m_blocks[index + 1].GetPosition());
						enemy->SetLastTimeMoving(m_elapsedTime);
						enemy->SetLastDirection(enemy->GetDirection());
					}
					else
					{
						enemy->SetWallHitted(true);
					}

				if (m_blocks[index + 1].GetBlockType() != EBlockType::EmptyBlock && m_blocks[index - 1].GetBlockType() != EBlockType::EmptyBlock && m_blocks[index + 17].GetBlockType() != EBlockType::EmptyBlock && m_blocks[index - 17].GetBlockType() != EBlockType::EmptyBlock)
				{
					enemy->SetWallHitted(true);
				}
				if (enemy->GetWallHitted() == true)
				{
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> dis(0, 3);

					uint16_t randomIndex = 0;
					randomIndex = dis(gen);

					while (enemy->GetLastDirection() != static_cast<Direction>(randomIndex))
					{
						enemy->SetDirection(static_cast<Direction>(randomIndex));
						randomIndex = dis(gen);

					}
					enemy->SetWallHitted(false);
				}

			}

		}
	}

}

bool Map::IsEnemyDead(const Enemy* enemy)
{
	if (enemy != nullptr) {

		uint16_t enemyIndexColumn = (enemy->GetPositionX() + 24) / 48;
		uint16_t enemyIndexLine = (enemy->GetPositionY() + 24) / 48;
		uint16_t index = enemyIndexLine * 17 + enemyIndexColumn;

		if (m_blocks[index].GetBlockType() == EBlockType::FireBlock)
		{
			std::vector<Enemy*>::iterator enemyIt = std::find(m_enemiesList.begin(), m_enemiesList.end(), enemy);
			enemy = nullptr;
			m_enemiesList.erase(enemyIt);
			m_numberOfMonsters--;
			return true;
		}
	}
	return false;
}

uint16_t Map::GetNumberOfMonsters() const
{
	return m_numberOfMonsters;
}

void Map::GenerateMapLayout()
{
	uint16_t indexBlockOnMap = 0;

	for (uint16_t lineIndex = 0; lineIndex < m_mapHeight; lineIndex++)
	{
		for (uint16_t columnIndex = 0; columnIndex < m_mapWidth; columnIndex++)
		{
			if (lineIndex == 0 || lineIndex == m_mapHeight - 1 || columnIndex == 0 || columnIndex == m_mapHeight - 1)
			{
				m_map[indexBlockOnMap] = EBlockType::BorderBlock;
			}

			else if (lineIndex % 2 == 0 && columnIndex % 2 == 0)
			{
				m_map[indexBlockOnMap] = EBlockType::WallBlock;
			}

			else
			{
				if (GenerateDestroyableBlock())
				{
					m_map[indexBlockOnMap] = EBlockType::StoneBlock;
				}
				else
				{
					m_map[indexBlockOnMap] = EBlockType::EmptyBlock;
				}
			}

			indexBlockOnMap++;
		}
	}

	m_map[18] = EBlockType::EmptyBlock;
	m_map[19] = EBlockType::EmptyBlock;
	m_map[35] = EBlockType::EmptyBlock;
}

PowerUp* Map::GetPower() const
{
	return m_powerUp;
}

std::vector<Enemy*> Map::GetEnemy() const
{
	return m_enemiesList;
}

void Map::SetElapsedTime(float time)
{
	m_elapsedTime = time;
}

void Map::ExplosionMarker(const sf::Vector2f& position)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<> dis(0, 20);
	const uint16_t randomNumber = dis(gen);

	const auto positionIndexColumn = static_cast<uint16_t>((position.x + (m_tileSize / 2.f)) / m_tileSize);
	const auto positionIndexLine = static_cast<uint16_t>((position.y + (m_tileSize / 2.f)) / m_tileSize);
	const auto indexBlock = positionIndexLine * 17 + positionIndexColumn;

	if (randomNumber == 20 && m_blocks[indexBlock].GetBlockType() == EBlockType::StoneBlock)
	{
		ClearBlock(position);

		if (m_powerUpPlaced == false && m_powerUp == nullptr) {
			GenerateRandomPowerUp(position);
			m_blocks[indexBlock].SetBlockType(EBlockType::PowerUpBlock);
			m_powerUpPlaced = true;
		}
	}

	else if (m_blocks[indexBlock].GetBlockType() == EBlockType::EmptyBlock)
	{
		m_blocks[indexBlock].SetBlockType(EBlockType::FireBlock);
		fireBlocks.push_back(indexBlock);
	}

	else if (m_blocks[indexBlock].GetBlockType() == EBlockType::PowerUpBlock)
	{
		RemovePowerUp();
	}
	else if (m_blocks[indexBlock].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexBlock].IsPortal() != true)
	{
		ClearBlock(position);
	}
	else if (m_blocks[indexBlock].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexBlock].IsPortal() == true)
	{
		m_portal->SetIsVisible(true);
		m_blocks[m_portalIndex].SetBlockType(EBlockType::PortalVisibleBlock);
	}
}

void Map::RemovePowerUp()
{
	m_powerUp = nullptr;
}

void Map::DetonateAllBombs()
{
	for (auto& bomb : m_bombsList)
		bomb->SetBombStatus(true);
}

void Map::SetDetonator(bool state)
{
	m_detonator = true;
}

bool Map::GetDetonator() const
{
	return m_detonator;
}

void Map::CreateBombsCollision(sf::Vector2f playerPosition)
{
	if (CheckBombsPositions(playerPosition) == true)
	{
		uint16_t bombIndexColumn = (m_bombsList.back()->GetBombShape().getPosition().x + 24) / 48;
		uint16_t bombIndexLine = (m_bombsList.back()->GetBombShape().getPosition().y + 24) / 48;
		uint16_t bombIndex = bombIndexLine * 17 + bombIndexColumn;

		uint16_t playerIndexColumn = (playerPosition.x + 24) / 48;
		uint16_t playerIndexLine = (playerPosition.y + 24) / 48;
		uint16_t playerIndex = playerIndexLine * 17 + playerIndexColumn;

		if (bombIndex > playerIndex || bombIndex < playerIndex)
		{
			m_blocks[bombIndex].SetBlockType(EBlockType::BombBlock);
		}
	}
}

void Map::ClearBlock(const sf::Vector2f& position)
{
	const auto positionIndexColumn = static_cast<uint16_t>((position.x + (m_tileSize / 2.f)) / m_tileSize);
	const auto positionIndexLine = static_cast<uint16_t>((position.y + (m_tileSize / 2.f)) / m_tileSize);
	const auto index = positionIndexLine * 17 + positionIndexColumn;

	if (m_blocks[index].GetBlockType() != EBlockType::EmptyBlock)
	{
		m_blocks[index].SetBlockType(EBlockType::EmptyBlock);
		m_map[index] = EBlockType::EmptyBlock;
		m_blocks[index].SetBlockTexture(&m_tileset, sf::IntRect(0, 0, static_cast<uint16_t>(m_tileSize), static_cast<uint16_t>(m_tileSize)));
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;

	for (const auto& block : m_blocks)
	{
		target.draw(block.GetBlockBody());
	}

	for (auto& bomb : m_bombsList)
	{
		target.draw(bomb->GetBombShape());
		bomb->Update(m_elapsedTime);
	}

	if (m_portal != nullptr && m_portal->GetIsVisible() == true)
	{
		target.draw(m_portal->GetShape());
		m_portal->Update(m_elapsedTime);
	}

	if (m_powerUp != nullptr)
	{
		target.draw(m_powerUp->GetShape());
	}

	for (auto& enemy : m_enemiesList)
	{
		if (enemy != nullptr)
		{
			target.draw(enemy->GetShape());
			enemy->UpdateAnimation(m_elapsedTime);
			target.draw(enemy->GetShape());
			enemy->UpdateAnimation(m_elapsedTime);
			target.draw(enemy->GetShape());
			enemy->UpdateAnimation(m_elapsedTime);
		}
	}
}