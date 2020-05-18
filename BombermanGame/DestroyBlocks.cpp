#include "DestroyBlocks.h"

DestroyBlocks::DestroyBlocks(sf::RectangleShape& m_player, Map& map)
	: m_player(m_player), m_map(map)
{
	// Empty
}

void DestroyBlocks::ChangeBlocks()
{
	int playerPositionIndexColumn = (GetPlayerPostion().x + 24) / 48;
	int playerPositionIndexLine = (GetPlayerPostion().y + 24) / 48;

	sf::Texture m_tileset;

	uint16_t IndexPlayer = playerPositionIndexColumn * 17 + playerPositionIndexLine;

	std::cout << IndexPlayer << "\n";

	//std::array<Block,289>* blocks = m_map.GetBlocks();

	//
	//// NORD
	//if (blocks[IndexPlayer + 1].GetBlockType() != EBlockType::WallBlock && blocks[IndexPlayer + 1].GetBlockType() != EBlockType::BorderBlock) {

	//	if (blocks[IndexPlayer + 2].GetBlockType() == EBlockType::StoneBlock && blocks[IndexPlayer + 1].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(blocks[IndexPlayer + 2]);
	//		m_map.PowerUpOrEmpty(blocks[IndexPlayer + 1]);

	//	}
	//	if (blocks[IndexPlayer + 2].GetBlockType() != EBlockType::StoneBlock && blocks[IndexPlayer + 1].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(blocks[IndexPlayer + 1]);

	//	}

	//	if (blocks[IndexPlayer + 2].GetBlockType() == EBlockType::StoneBlock && blocks[IndexPlayer + 1].GetBlockType() == EBlockType::EmptyBlock)
	//	{
	//		m_map.PowerUpOrEmpty(blocks[IndexPlayer + 2]);
	//	}
	//}

	//if (m_map.m_blocks[IndexPlayer - 1].GetBlockType() != EBlockType::WallBlock && m_map.m_blocks[IndexPlayer - 1].GetBlockType() != EBlockType::BorderBlock) {

	//	if (m_map.m_blocks[IndexPlayer - 2].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 2]);
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 1]);

	//	}
	//	if (m_map.m_blocks[IndexPlayer - 2].GetBlockType() != EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 1]);

	//	}

	//	if (m_map.m_blocks[IndexPlayer - 2].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 1].GetBlockType() == EBlockType::EmptyBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 2]);
	//	}
	//}

	//if (m_map.m_blocks[IndexPlayer - 17].GetBlockType() != EBlockType::WallBlock && m_map.m_blocks[IndexPlayer - 17].GetBlockType() != EBlockType::BorderBlock) {

	//	if (m_map.m_blocks[IndexPlayer - 34].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 17].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 34]);
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 17]);

	//	}
	//	if (m_map.m_blocks[IndexPlayer - 34].GetBlockType() != EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 17].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 17]);

	//	}

	//	if (m_map.m_blocks[IndexPlayer - 34].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer - 17].GetBlockType() == EBlockType::EmptyBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer - 34]);
	//	}
	//}

	//if (m_map.m_blocks[IndexPlayer + 17].GetBlockType() != EBlockType::WallBlock && m_map.m_blocks[IndexPlayer + 17].GetBlockType() != EBlockType::BorderBlock) {

	//	if (m_map.m_blocks[IndexPlayer + 34].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer + 17].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer + 34]);
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer + 17]);

	//	}
	//	if (m_map.m_blocks[IndexPlayer + 34].GetBlockType() != EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer + 17].GetBlockType() == EBlockType::StoneBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer + 17]);

	//	}

	//	if (m_map.m_blocks[IndexPlayer + 34].GetBlockType() == EBlockType::StoneBlock && m_map.m_blocks[IndexPlayer + 17].GetBlockType() == EBlockType::EmptyBlock)
	//	{
	//		m_map.PowerUpOrEmpty(m_map.m_blocks[IndexPlayer + 34]);
	//	}
	//}
}

sf::Vector2f DestroyBlocks::GetPlayerPostion() const
{
	return m_player.getPosition();
}