#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

#include "BlockType.h"
#include "Collider.h"
#include "Block.h"
#include "Portal.h"
#include "PowerUp.h"
#include "Bomb.h"

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

public:
	void SetElapsedTime(float time) { m_elapsedTime = time; };
	void ExplosionMarker(const sf::Vector2f& position);
	void RemovePowerUp();
	void ClearBlock(const sf::Vector2f& position);
	void GenerateBombs(const sf::Vector2f& playersPosition,const uint16_t& bombRadius,const float& timeElapsed, const uint16_t& maxNoBombs);
	uint16_t GetNoBombsDisplayed() const;
	void EarlyExplode(Bomb* bomb);

private:
	void GenerateMapLayout();
	bool GenerateDestroyableBlock() const;
	void GenerateRandomTeleport();
	void GenerateRandomPowerUp(const sf::Vector2f& position);
	bool CheckBombsPositions(sf::Vector2f playerPosition);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

public:
	std::vector<Bomb*> m_bombsList;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Texture m_barTexture;
	sf::Sprite m_bar;
	sf::Font m_font;
	sf::Text m_text;

	static const uint16_t m_mapWidth = 17;
	static const uint16_t m_mapHeight = 17;

	float m_elapsedTime;
	Portal* m_portal;

	sf::Vector2f lastPlayerPos;

	uint16_t m_numberOfMonsters = 0;

	PowerUp* m_powerUp;
	bool m_powerUpPlaced = false;

	std::array<EBlockType, m_mapHeight * m_mapWidth> m_map;
	std::array<Block, m_mapHeight * m_mapWidth> m_blocks;
};
