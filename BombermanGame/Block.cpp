#include "Block.h"

Block::Block() : m_blockType(EBlockType::EmptyBlock), m_blockBody(sf::Vector2f(48.f, 48.f)), isPortal(false)
{
	// empty
}

EBlockType Block::GetBlockType() const
{
	return m_blockType;
}

sf::RectangleShape Block::GetBlockBody() const
{
	return m_blockBody;
}

Collider Block::GetCollider()
{
	return Collider(m_blockBody);
}

sf::Vector2f Block::GetPosition()
{
	return m_blockBody.getPosition();
}

bool Block::GetIsPortal() const
{
	return isPortal;
}

void Block::SetBlockType(const EBlockType& blockType)
{
	m_blockType = blockType;
}

void Block::SetPosition(const sf::Vector2f& coordinates)
{
	m_blockBody.setPosition(coordinates);
}

void Block::SetBlockTexture(sf::Texture* texture, sf::IntRect blockTexture)
{
	m_blockBody.setTexture(texture);
	m_blockBody.setTextureRect(blockTexture);
}

void Block::SetIsPortal(bool state)
{
	isPortal = state;
}
