#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "BlockType.h"
#include <iostream>

class Block
{
public:
	Block();
	~Block() = default;
	Block(const Block& other) = default;
	Block(Block&& other) noexcept = default;
	Block& operator=(const Block& other) = default;
	Block& operator=(Block&& other) noexcept = default;

public:
	EBlockType GetBlockType() const;
	sf::RectangleShape GetBlockBody() const;
	Collider GetCollider();
	sf::Vector2f GetPosition();
	bool GetIsPortal() const;

public:
	void SetBlockType(const EBlockType& blockType);
	void SetPosition(const sf::Vector2f& coordinates);
	void SetBlockTexture(sf::Texture* texture, sf::IntRect);
	void SetIsPortal(bool state);
private:
	sf::RectangleShape m_blockBody;
	EBlockType m_blockType;
	const sf::Texture m_blockTexture;

	bool isPortal;
};