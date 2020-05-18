#include "Explosion.h"

Explosion::Explosion(const sf::Vector2f& bombPosition, const uint16_t& radius, std::array<EBlockType, 17 * 17>& m_map, std::array<Block, 17 * 17>& m_blocks)
	:m_center(bombPosition), m_radius(radius), m_map(m_map), m_blocks(m_blocks)
{
	m_explosionShape.setPosition(m_center);
	PlaceExplosion();
}

void Explosion::Update()
{
}

void Explosion::PlaceExplosion()
{
	m_explosionTexture.loadFromFile("../_external/sprites/explosion.png");
	m_explosionTexture.setSmooth(true);
	m_explosionShape.setTexture(&m_explosionTexture);

	uint16_t IndexBomba = (m_center.x / 48) + m_center.y / 48;

	// WEST
	if (m_blocks[IndexBomba - 1].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexBomba - 1].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexBomba - 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			//toata partea stanga
			m_explosionShape.setTextureRect(sf::IntRect(0, 144, 48, 144));
		}
		if (m_blocks[IndexBomba - 2].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexBomba - 1].GetBlockType() == EBlockType::StoneBlock)
		{
			if (m_blocks[IndexBomba - 2].GetBlockType() == EBlockType::BorderBlock || m_blocks[IndexBomba - 2].GetBlockType() == EBlockType::WallBlock)
			{// doar prima bucatica de langa centru
				m_explosionShape.setTextureRect(sf::IntRect(48, 96, 240, 240));
			}
			//else
				//toata partea stanga
		}

		if (m_blocks[IndexBomba - 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba - 1].GetBlockType() == EBlockType::EmptyBlock)
		{
			//toata partea stanga
		}
	}

	if (m_blocks[IndexBomba + 1].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexBomba + 1].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexBomba + 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			//toata partea de sus
		}
		if (m_blocks[IndexBomba + 2].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexBomba + 1].GetBlockType() == EBlockType::StoneBlock)
		{
			if (m_blocks[IndexBomba + 2].GetBlockType() == EBlockType::BorderBlock || m_blocks[IndexBomba + 2].GetBlockType() == EBlockType::WallBlock)
			{
				// doar prima bucatica de langa centru in sus
			}
			//else
				//toata partea de sus
		}

		if (m_blocks[IndexBomba + 2].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba + 1].GetBlockType() == EBlockType::EmptyBlock)
		{
			//toata partea de sus
		}
	}

	if (m_blocks[IndexBomba - 17].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexBomba - 17].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexBomba - 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			//toata partea din stanga
		}
		if (m_blocks[IndexBomba - 34].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexBomba - 17].GetBlockType() == EBlockType::StoneBlock)
		{
			if (m_blocks[IndexBomba - 34].GetBlockType() == EBlockType::BorderBlock || m_blocks[IndexBomba - 34].GetBlockType() == EBlockType::WallBlock)
			{// doar prima bucatica de langa centru in stanga
				m_explosionShape.setTextureRect(sf::IntRect(48, 96, 240, 240));
			}
			//else
				//toata partea stanga
		}
	}

	if (m_blocks[IndexBomba + 17].GetBlockType() != EBlockType::WallBlock && m_blocks[IndexBomba + 17].GetBlockType() != EBlockType::BorderBlock) {

		if (m_blocks[IndexBomba + 34].GetBlockType() == EBlockType::StoneBlock && m_blocks[IndexBomba + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			//toata bucatica din dreapta
		}
		if (m_blocks[IndexBomba + 34].GetBlockType() != EBlockType::StoneBlock && m_blocks[IndexBomba + 17].GetBlockType() == EBlockType::StoneBlock)
		{
			if (m_blocks[IndexBomba + 34].GetBlockType() == EBlockType::BorderBlock || m_blocks[IndexBomba + 34].GetBlockType() == EBlockType::WallBlock)
			{// doar prima bucatica de langa centru in dreapta
			}
			//else
				//toata partea dreapta
		}
	}
}