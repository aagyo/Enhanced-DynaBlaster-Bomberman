#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "BlockType.h"
#include <array>
#include "Map.h"
#include "Player.h"

class DestroyBlocks 
{
public:
	DestroyBlocks() = default;
	~DestroyBlocks() = default;

	DestroyBlocks(const DestroyBlocks& other) = default;
	DestroyBlocks(DestroyBlocks&& other) noexcept = default;
	DestroyBlocks& operator=(DestroyBlocks&& other) noexcept = default;

public:
	DestroyBlocks(sf::RectangleShape& m_player, Map &map);

public:
	void ChangeBlocks();
	sf::Vector2f GetPlayerPostion() const;

private:
	static const int m_mapWidth = 17;
	static const int m_mapHeight = 17;

	sf::RectangleShape& m_player;
	Map &m_map;

};