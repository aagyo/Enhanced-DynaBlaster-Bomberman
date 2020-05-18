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

void Map::GenerateRandomPowerUp(const sf::Vector2f& position) {


	m_powerUp = new PowerUp(sf::Vector2f(position));
	m_powerUp->CreateRandomPowerUp();


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

void Map::PowerUpOrEmpty(Block& block)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 20);

	uint16_t randomNumber = dis(gen);

	if (randomNumber == 20)
	{
		if (m_powerUpPlaced == false && m_powerUp == nullptr) {
			GenerateRandomPowerUp(block.GetPosition());
			block.SetBlockType(EBlockType::PowerUpBlock);
			block.SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
			m_powerUpPlaced = true;
		}

	}

	else 
	{
		block.SetBlockType(EBlockType::EmptyBlock);
		block.SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
	}
}

void Map::RemovePowerUp()
{
	m_powerUp = nullptr;
}

void Map::ClearBlock(const sf::Vector2f& position)
{
	uint16_t playerPositionIndexColumn = (position.x + 24) / 48;
	uint16_t playerPositionIndexLine = (position.y + 24) / 48;

	uint16_t index = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	m_blocks[index].SetBlockType(EBlockType::EmptyBlock);
	m_map[index] == EBlockType::EmptyBlock;
	m_blocks[index].SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
}



void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_tileset;

	for (const Block& block : m_blocks)
	{
		target.draw(block.GetBlockBody());
	}

	//if (m_portal->GetIsVisible() == true) {
	target.draw(m_portal->GetShape());
	m_portal->Update(m_elapsedTime);

	if (m_powerUp != nullptr)
		target.draw(m_powerUp->GetShape());
}

