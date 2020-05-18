#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "BlockType.h"
#include "Collider.h"
#include "Block.h"
#include "Portal.h"
#include "PowerUp.h"

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
	void CreateTilesOnMap(const sf::Vector2u& tileSize);
	Block& GetBlock(uint16_t position);

public:
	static const uint16_t GetWidth();
	static const uint16_t GetHeight();


private:
	void GenerateMapLayout();
	bool GenerateDestroyableBlock() const;
	void GenerateRandomTeleport();
	void GenerateRandomPowerUp(const sf::Vector2f& position);

public:
	void SetElapsedTime(float time) { m_elapsedTime = time; };
	void PowerUpOrEmpty(Block& position);
	void RemovePowerUp();
	void ClearBlock(const sf::Vector2f& position);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	static const uint16_t m_mapWidth = 17;
	static const uint16_t m_mapHeight = 17;

	float m_elapsedTime;
	Portal* m_portal;

	uint16_t m_numberOfMonsters = 0;

	PowerUp* m_powerUp;
	bool m_powerUpPlaced = false;

	std::array<EBlockType, m_mapHeight * m_mapWidth> m_map;
	std::array<Block, m_mapHeight * m_mapWidth> m_blocks;

};
