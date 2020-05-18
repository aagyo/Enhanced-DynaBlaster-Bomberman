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
	float playerPositionIndexColumn = GetPlayerPostion().x / 48.f;
	float playerPositionIndexLine = GetPlayerPostion().y / 48.f;
	uint16_t indexInMap = 0;

	// WEST
	if (m_blocks[indexInMap - 1].GetBlockType() != EBlockType::WallBlock) {

		if (m_blocks[indexInMap - 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexInMap - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap - 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[indexInMap - 1].SetBlockType(EBlockType::EmptyBlock);
		}
		if (m_blocks[indexInMap - 2].GetBlockType() == EBlockType::WallBlock && m_blocks[indexInMap - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap - 1].SetBlockType(EBlockType::EmptyBlock);

		}
	}

	if (m_blocks[indexInMap + 1].GetBlockType() != EBlockType::WallBlock) {

		if (m_blocks[indexInMap + 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexInMap + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap + 2].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[indexInMap + 1].SetBlockType(EBlockType::EmptyBlock);

		}
		if (m_blocks[indexInMap + 2].GetBlockType() == EBlockType::WallBlock && m_blocks[indexInMap + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap + 1].SetBlockType(EBlockType::EmptyBlock);

		}
	}

	if (m_blocks[indexInMap - 17].GetBlockType() != EBlockType::WallBlock) {

		if (m_blocks[indexInMap - 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexInMap - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap - 34].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[indexInMap - 17].SetBlockType(EBlockType::EmptyBlock);

		}
		if (m_blocks[indexInMap - 34].GetBlockType() == EBlockType::WallBlock && m_blocks[indexInMap - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap - 17].SetBlockType(EBlockType::EmptyBlock);

		}
	}

	if (m_blocks[indexInMap + 17].GetBlockType() != EBlockType::WallBlock) {

		if (m_blocks[indexInMap + 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[indexInMap + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap + 34].SetBlockType(EBlockType::EmptyBlock);
			m_blocks[indexInMap + 17].SetBlockType(EBlockType::EmptyBlock);

		}
		if (m_blocks[indexInMap + 34].GetBlockType() == EBlockType::WallBlock && m_blocks[indexInMap + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			m_blocks[indexInMap + 17].SetBlockType(EBlockType::EmptyBlock);

		}
	}

}

sf::Vector2f DestroyBlocks::GetPlayerPostion() const
{
	return m_player.getPosition();
}