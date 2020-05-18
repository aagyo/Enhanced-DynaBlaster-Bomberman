#include "Block.h"

Block::Block() :
	m_blockBody(sf::Vector2f(m_tileSize, m_tileSize)), m_blockType(EBlockType::EmptyBlock), isPortal(false)
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

sf::Vector2f Block::GetPosition() const
{
	return m_blockBody.getPosition();
}

bool Block::IsPortal() const
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

void Block::SetBlockTexture(sf::Texture* texture, const sf::IntRect& blockTexture)
{
	m_blockBody.setTexture(texture);
	m_blockBody.setTextureRect(blockTexture);
}

void Block::SetIsPortal(bool state)
{
	isPortal = state;
}