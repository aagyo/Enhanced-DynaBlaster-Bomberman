#include "DestroyBlocks.h"

DestroyBlocks::DestroyBlocks(sf::RectangleShape& m_player, std::array<EBlockType, 17 * 17>& m_map, std::array<Block, 17 * 17>& m_blocks)
	: m_player(m_player),
	m_map(m_map),
	m_blocks(m_blocks)
{
	// Empty
}

void DestroyBlocks::ChangeBlocks()
{
	int playerPositionIndexColumn = (GetPlayerPostion().x + 24) / 48;
	int playerPositionIndexLine = (GetPlayerPostion().y + 24) / 48;



	sf::Texture m_tileset;
	
	m_tileset.loadFromFile("../_external/sprites/boamberman.png");

	std::cout << playerPositionIndexColumn << " " << playerPositionIndexLine << "\n";


	uint16_t IndexPlayer = playerPositionIndexLine * 17 + playerPositionIndexColumn;

	std::cout << IndexPlayer << "\n";

	// WEST
	if (m_blocks[IndexPlayer - 1].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexPlayer - 1].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexPlayer - 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer - 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 1].SetBlockType(EBlockType::EmptyBlock);

			m_blocks[IndexPlayer - 1].SetBlockTexture(&m_tileset, sf::IntRect(144, 0, 48, 48));
			m_blocks[IndexPlayer - 2].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));

			std::cout << "change ";
		}
		if (m_blocks[IndexPlayer - 2].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer - 1].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 1].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}

		if (m_blocks[IndexPlayer - 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::EmptyBlock)
		{
			m_blocks[IndexPlayer - 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 2].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
	}

	if (m_blocks[IndexPlayer + 1].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexPlayer + 1].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexPlayer + 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer + 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 1].SetBlockType(EBlockType::EmptyBlock);

			m_blocks[IndexPlayer + 2].SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
			m_blocks[IndexPlayer + 1].SetBlockTexture(&m_tileset, sf::IntRect(0, 0, 48, 48));
			std::cout << "change ";
		}
		if (m_blocks[IndexPlayer + 2].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexPlayer + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer + 1].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 1].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}

		if (m_blocks[IndexPlayer + 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer + 1].GetBlockType() == EBlockType::EmptyBlock)
		{
			m_blocks[IndexPlayer + 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 2].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
	}

	if (m_blocks[IndexPlayer - 17].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexPlayer - 17].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexPlayer - 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer - 34].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 17].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 17].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			m_blocks[IndexPlayer - 34].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
		if (m_blocks[IndexPlayer - 34].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexPlayer - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer - 17].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer - 17].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
	}

	if (m_blocks[IndexPlayer + 17].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexPlayer + 17].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexPlayer + 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexPlayer + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer + 34].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 17].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 17].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			m_blocks[IndexPlayer + 34].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
		if (m_blocks[IndexPlayer + 34].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexPlayer + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[IndexPlayer + 17].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[IndexPlayer + 17].SetBlockTexture(&m_tileset, sf::IntRect(48, 0, 48, 48));
			std::cout << "change ";
		}
	}
}


sf::Vector2f DestroyBlocks::GetPlayerPostion() const
{
	return m_player.getPosition();
}