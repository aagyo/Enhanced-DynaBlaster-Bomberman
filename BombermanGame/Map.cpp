#include "Map.h"
#include "PlayState.h"
#include <random>

// STERGE DE AICI
#include <iostream>

void Map::CreateTilesOnMap(const sf::Vector2u& tileSize)
{
	uint16_t tileNumber = 0;

	GenerateMapLayout();

	m_tileset.loadFromFile("../_external/sprites/sprites2.png");
	m_tileset.setSmooth(true);

	for (uint16_t heightIndex = 0; heightIndex < m_mapHeight; heightIndex++)
	{
		for (uint16_t widthIndex = 0; widthIndex < m_mapWidth; widthIndex++)
		{

			uint16_t tileNumberIndex = static_cast<uint16_t>(m_map[tileNumber]);

			uint16_t textureLineIndex = tileNumberIndex % (m_tileset.getSize().x / tileSize.x);
			uint16_t textureColumnIndex = tileNumberIndex / (m_tileset.getSize().x / tileSize.x);

			m_blocks[tileNumber].SetPosition(sf::Vector2f(widthIndex * tileSize.x, heightIndex * tileSize.y));
			m_blocks[tileNumber].SetBlockType(m_map[tileNumber]);
			m_blocks[tileNumber].SetBlockTexture(&m_tileset, sf::IntRect(textureLineIndex * tileSize.x, textureColumnIndex * tileSize.y, tileSize.x, tileSize.y));

			tileNumber++;
		}
	}

	GenerateRandomTeleport();

	m_barTexture.loadFromFile("../_external/sprites/bar.png");
	m_barTexture.setSmooth(true);
	m_bar.setTexture(m_barTexture);
	m_bar.setPosition(0.f, 816.f);

	m_font.loadFromFile("../_external/font/bm.ttf");
	m_text.setString("BOMBS - 9   LIFES - 3   CLOCK - 2:30");
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setPosition(150.f, 816.f);
}

Block& Map::GetBlock(uint16_t position)
{
	return m_blocks[position];
}

const uint16_t Map::GetWidth()
{
	return m_mapWidth;
}

const uint16_t Map::GetHeight()
{
	return m_mapHeight;
}


bool Map::GenerateDestroyableBlock() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	return dis(gen);
}

void Map::GenerateBombs(const sf::Vector2f& playersPosition, const uint16_t& bombRadius, const float& timeElapsed, const uint16_t& maxNoBombs)
{
	if (m_bombsList.size() <= maxNoBombs && !m_bombsList.empty())
	{
		if (CheckBombsPositions(playersPosition))
		{
 			Bomb* newBomb = new Bomb(m_blocks[static_cast<uint16_t>(round(playersPosition.x / 48))].GetPosition().x,
				m_blocks[static_cast<uint16_t>(round(playersPosition.y / 48))].GetPosition().x,
				bombRadius, timeElapsed);
			m_bombsList.push_back(newBomb);
			lastPlayerPos = playersPosition;
		}
	}
	if(m_bombsList.empty())
	{
		Bomb* newBomb = new Bomb(m_blocks[static_cast<uint16_t>(round(playersPosition.x / 48))].GetPosition().x,
			m_blocks[static_cast<uint16_t>(round(playersPosition.y / 48))].GetPosition().x,
			bombRadius, timeElapsed);
		m_bombsList.push_back(newBomb);
	}
}

uint16_t Map::GetNoBombsDisplayed() const
{
	return m_bombsList.size();
}

void Map::GenerateRandomTeleport() {

	if (m_numberOfMonsters == 0) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, m_blocks.size() - 1);

		uint16_t randomIndex = 0;

		while (m_map[randomIndex] != EBlockType::PortalBlock)
		{
			randomIndex = dis(gen);

			if (m_map[randomIndex] == EBlockType::StoneBlock) {

				m_blocks[randomIndex].SetBlockType(EBlockType::PortalBlock);
				m_blocks[randomIndex].SetIsPortal(true);
				m_map[randomIndex] = EBlockType::PortalBlock;

			}

		}

		m_portal = new Portal(sf::Vector2f(m_blocks[randomIndex].GetBlockBody().getPosition()));
	}
}

void Map::GenerateRandomPowerUp(const sf::Vector2f& position)
{
	m_powerUp = new PowerUp(sf::Vector2f(position));
	m_powerUp->CreateRandomPowerUp();
}

bool Map::CheckBombsPositions(sf::Vector2f playerPosition)
{
	bool flag = false;
	for (auto& bomb : m_bombsList)
	{
		if (bomb->GetBombShape().getPosition().x != playerPosition.x && bomb->GetBombShape().getPosition().y != playerPosition.y)
			flag = true;
	}
	return flag;
}

void Map::EarlyExplode(Bomb* bomb)
{
	uint16_t bombIndexColumn = (bomb->GetBombShape().getPosition().x + 24) / 48;
	uint16_t bombIndexLine = (bomb->GetBombShape().getPosition().y + 24) / 48;
	uint16_t index = bombIndexLine * 17 + bombIndexColumn;
	if (m_blocks[index].GetBlockType() == EBlockType::FireBlock)
		bomb->SetBombStatus(true);
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
				// std::cout << "3 ";
			}

			else if (lineIndex % 2 == 0 && columnIndex % 2 == 0)
			{
				m_map[indexBlockOnMap] = EBlockType::WallBlock;
				// std::cout << "2 ";
			}

			else
			{
				if (GenerateDestroyableBlock())
				{
					m_map[indexBlockOnMap] = EBlockType::StoneBlock;
					// std::cout << "1 ";
				}
				else
				{
					m_map[indexBlockOnMap] = EBlockType::EmptyBlock;
					// std::cout << "0 ";
				}
			}

			indexBlockOnMap++;
		}
	}

	m_map[18] = EBlockType::EmptyBlock;
	m_map[19] = EBlockType::EmptyBlock;
	m_map[35] = EBlockType::EmptyBlock;
}

void Map::ExplosionMarker(const sf::Vector2f& position)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 20);

	uint16_t randomNumber = dis(gen);

	uint16_t positionIndexColumn = (position.x + 24) / 48;
	uint16_t positionIndexLine = (position.y + 24) / 48;
	uint16_t index = positionIndexLine * 17 + positionIndexColumn;

	if (randomNumber == 20 && m_blocks[index].GetBlockType() == EBlockType::StoneBlock)
	{
		ClearBlock(position);
		if (m_powerUpPlaced == false && m_powerUp == nullptr) {
			GenerateRandomPowerUp(position);
			m_blocks[index].SetBlockType(EBlockType::PowerUpBlock);
			m_powerUpPlaced = true;
		}
	}
	else if (m_blocks[index].GetBlockType() == EBlockType::EmptyBlock)
	{
		m_blocks[index].SetBlockType(EBlockType::FireBlock);
	}
	else if (m_blocks[index].GetBlockType() == EBlockType::PowerUpBlock)
		RemovePowerUp();
	else if (m_blocks[index].GetBlockType() == EBlockType::StoneBlock)
		ClearBlock(position);
	else if (m_blocks[index].GetBlockType() == EBlockType::StoneBlock && m_portal->GetPortalPosition() == position)
	{
		ClearBlock(position);
		m_blocks[index].SetBlockType(EBlockType::PortalBlock);
		m_portal->SetIsVisible(true);
	}
}

void Map::RemovePowerUp()
{
	m_powerUp = nullptr;
}

void Map::ClearBlock(const sf::Vector2f& position)
{
	uint16_t positionIndexColumn = (position.x + 24) / 48;
	uint16_t positionIndexLine = (position.y + 24) / 48;

	uint16_t index = positionIndexLine * 17 + positionIndexColumn;
	if (m_blocks[index].GetBlockType() != EBlockType::EmptyBlock)
	{
		m_blocks[index].SetBlockType(EBlockType::EmptyBlock);
		m_map[index] == EBlockType::EmptyBlock;
		m_blocks[index].SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_tileset;

	for (const Block& block : m_blocks)
	{
		target.draw(block.GetBlockBody());
	}

	for (auto& bomb : m_bombsList)
	{
		target.draw(bomb->GetBombShape());
		bomb->Update(m_elapsedTime);
	}

	if (m_portal->GetIsVisible() == true)
	{
		target.draw(m_portal->GetShape());
		m_portal->Update(m_elapsedTime);
	}

	if (m_powerUp != nullptr)
	{
		target.draw(m_powerUp->GetShape());
	}

	target.draw(m_bar);
	target.draw(m_text);
}