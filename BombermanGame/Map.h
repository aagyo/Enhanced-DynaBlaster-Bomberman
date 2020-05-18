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
#include "Enemy.h"
#include "EnemyDirection.h"
#include "LevelState.h"

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
	PowerUp* GetPower();
	std::vector<Enemy*> GetEnemy() const;

public:
	static const uint16_t GetWidth();
	static const uint16_t GetHeight();

public:
	void SetElapsedTime(float time) { m_elapsedTime = time; };
	void ExplosionMarker(const sf::Vector2f& position);
	void RemovePowerUp();
	void ClearBlock(const sf::Vector2f& position);
	void IsPortal(Block& block);
	void GenerateRandomTeleport();
	bool IsPortalGenerate();

	void GenerateBombs(const sf::Vector2f& playersPosition, const uint16_t& bombRadius, const float& timeElapsed, const uint16_t& maxNoBombs);
	uint16_t GetNoBombsDisplayed() const;
	void EarlyExplode(Bomb* bomb);
	void ClearFireBlocks();
	void MoveEnemy();
	bool IsEnemyDead(const Enemy* enemy);
	uint16_t GetNumberOfMonsters();
	void DetonateAllBombs();
	void SetDetonator(bool state);
	bool GetDetonator() const;
	void CreateBombsCollision(sf::Vector2f playerPosition);

private:
	bool CheckBombsPositions(sf::Vector2f playerPosition);
	void GenerateMapLayout();
	bool GenerateDestroyableBlock() const;
	void GenerateRandomPowerUp(const sf::Vector2f& position);
	void GenerateRandomEnemy();
	void PlaceEnemies(const uint8_t randomIndex);
	void CreateEnemies();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

public:
	std::vector<Bomb*> m_bombsList;

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Texture m_barTexture;

	std::vector<Enemy*> m_enemiesList;
	uint8_t m_currentEnemy = 0;

	static const uint16_t m_mapWidth = 17;
	static const uint16_t m_mapHeight = 17;
	bool m_detonator = false;

	float m_elapsedTime;
	Portal* m_portal;
	bool m_portalGenerated = false;

	std::vector<uint16_t> fireBlocks;

	sf::Vector2f lastPlayerPos;

	uint16_t m_numberOfMonsters = LevelState::m_currentLevel + 1;

	PowerUp* m_powerUp;
	bool m_powerUpPlaced = false;

	Enemy* m_enemy;

	std::array<EBlockType, m_mapHeight * m_mapWidth> m_map;
	std::array<Block, m_mapHeight * m_mapWidth> m_blocks;
};
