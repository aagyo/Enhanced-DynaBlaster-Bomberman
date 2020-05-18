#include "Map.h"
#include <random>

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

			m_blocks[tileNumber].SetPosition(sf::Vector2f( widthIndex * tileSize.x, heightIndex * tileSize.y));
			m_blocks[tileNumber].SetBlockType(m_map[tileNumber]);
			m_blocks[tileNumber].SetBlockTexture(&m_tileset, sf::IntRect(textureLineIndex * tileSize.x, textureColumnIndex * tileSize.y, tileSize.x, tileSize.y));

			tileNumber++;
		}
	}
}

Block Map::GetBlock(uint16_t position) const
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
				std::cout << "3 ";
			}

			else if (lineIndex % 2 == 0 && columnIndex % 2 == 0)
			{
				m_map[indexBlockOnMap] = EBlockType::WallBlock;
				std::cout << "2 ";
			}

			else
			{
				if (GenerateDestroyableBlock())
				{
					std::cout << "1 ";
					m_map[indexBlockOnMap] = EBlockType::StoneBlock;
				}
				else
				{
					std::cout << "0 ";
					m_map[indexBlockOnMap] = EBlockType::EmptyBlock;
				}
			}

			indexBlockOnMap++;
		}
	}

	m_map[18] = EBlockType::EmptyBlock;
	m_map[19] = EBlockType::EmptyBlock;
	m_map[35] = EBlockType::EmptyBlock;

	std::cout << "\n";

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_tileset;

	for (const Block& block : m_blocks)
	{
		target.draw(block.GetBlockBody());
	}
}