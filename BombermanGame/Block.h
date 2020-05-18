#pragma once
#include "Collider.h"
#include "BlockType.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class Block
{
public:
	Block();
	~Block() = default;
	Block(const Block& other) = default;
	Block(Block&& other) noexcept = default;

public:
	EBlockType GetBlockType() const;
	sf::RectangleShape GetBlockBody() const;
	sf::Vector2f GetPosition() const;
	Collider GetCollider();

public:
	bool IsPortal() const;

public:
	void SetBlockType(const EBlockType& blockType);
	void SetPosition(const sf::Vector2f& coordinates);
	void SetBlockTexture(sf::Texture* texture, const sf::IntRect& blockTexture);
	void SetIsPortal(bool state);

protected:
	const float m_tileSize = 48.f;
	
private:
	sf::RectangleShape m_blockBody;
	const sf::Texture m_blockTexture;
	EBlockType m_blockType;
	bool isPortal;
};