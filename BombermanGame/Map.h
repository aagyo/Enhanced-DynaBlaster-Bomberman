#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "BlockType.h"
#include "Collider.h"
#include "Block.h"

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map() = default;
	~Map() = default;
	Map(const Map& other) = default;
	Map(Map&& other) noexcept = default;
	Map& operator=(const Map& other) = default;
	Map& operator=(Map&& other) noexcept = default;

public:
	Block GetBlock(uint16_t position) const;
	std::array<EBlockType, 289> GetMap() const;
	std::array<Block, 289> GetBlocks() const;
	static const uint16_t GetWidth();
	static const uint16_t GetHeight();

public:
	void CreateTilesOnMap(const sf::Vector2u& tileSize);

private:
	void GenerateMapLayout();
	bool GenerateDestroyableBlock() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray m_vertices;
	static const uint16_t m_mapWidth = 17;
	static const uint16_t m_mapHeight = 17;

	//schimba
public:
	std::array<EBlockType, m_mapHeight * m_mapWidth> m_map;
	std::array<Block, m_mapHeight * m_mapWidth> m_blocks;
	sf::Texture m_tileTexture;
};