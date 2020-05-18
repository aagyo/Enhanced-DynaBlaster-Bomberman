#pragma once
#include <array>
#include <vector>

#include "BlockType.h"
#include "Block.h"
#include "Portal.h"
#include "PowerUp.h"
#include "Bomb.h"
#include "Enemy.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Font.hpp"

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
	Block& GetBlock(uint16_t position);
	PowerUp* GetPower() const;
	std::vector<Enemy*> GetEnemy() const;

public:
	void CreateTilesOnMap(const sf::Vector2u& tileSize);
	void SetElapsedTime(float time);
	void ExplosionMarker(const sf::Vector2f& position);
	void ClearBlock(const sf::Vector2f& position);
	void GenerateBombs(const sf::Vector2f& playersPosition, const uint16_t bombRadius, const float timeElapsed, const uint16_t maxNoBombs);
	void EarlyExplode(Bomb* bomb);
	void IsPortal();

public:
	void GenerateRandomTeleport();
	bool IsPortalGenerate();
	void ClearFireBlocks();
	void MoveEnemy();
	bool IsEnemyDead(const Enemy* enemy);
	void RemovePowerUp();
	void DetonateAllBombs();
	void SetDetonator(bool state);
	bool GetDetonator() const;
	void CreateBombsCollision(sf::Vector2f playerPosition);

public:
	uint16_t GetNumberOfBombsDisplayed() const;
	uint16_t GetNumberOfMonsters() const;

public:
	std::vector<Bomb*> m_bombsList;

public:
	static uint16_t GetWidth();
	static uint16_t GetHeight();

protected:
	const float m_tileSize = 48.f;

private:
	void GenerateMapLayout();
	void GenerateRandomPowerUp(const sf::Vector2f& position);
	void GenerateRandomEnemy();
	bool CheckBombsPositions(sf::Vector2f playerPosition);
	static bool GenerateDestroyableBlock();
	void ChangeStageTexture();
	void CreateEnemies();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Texture m_barTexture;

private:
	Portal* m_portal;
	bool m_portalGenerated = false;
	uint16_t m_portalIndex;
	PowerUp* m_powerUp;
	bool m_powerUpPlaced = false;
	bool m_detonator = false;
	uint16_t m_numberOfMonsters;
	std::vector<uint16_t> fireBlocks;
	sf::Vector2f lastPlayerPos;
	std::vector<Enemy*> m_enemiesList;

private:
	float m_elapsedTime;
	static const uint16_t m_mapWidth = 17;
	static const uint16_t m_mapHeight = 17;
	std::array<EBlockType, m_mapHeight * m_mapWidth> m_map;
	std::array<Block, m_mapHeight * m_mapWidth> m_blocks;
};