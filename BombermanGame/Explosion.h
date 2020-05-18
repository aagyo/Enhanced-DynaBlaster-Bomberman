#pragma once
#include "Animation.h"
#include "Block.h"
#include "BlockType.h"
#include <array>

class Explosion
{

public:
	Explosion() = default;
	~Explosion() = default;
public:
	Explosion(const sf::Vector2f& bombPosition, const uint16_t& radius, std::array<EBlockType, 17 * 17>& m_map, std::array<Block, 17 * 17>& m_blocks);
	void Update();

private:
	void PlaceExplosion();

private:
	static const int m_mapWidth = 17;
	static const int m_mapHeight = 17;
	std::array<EBlockType, m_mapWidth * m_mapHeight>& m_map;
	std::array<Block, m_mapWidth * m_mapHeight>& m_blocks;
	sf::Vector2f m_center;
	uint16_t m_radius;
	float m_explosionTime = 0;
	sf::RectangleShape m_explosionShape;
	sf::Texture m_explosionTexture;
	struct AnimationInfo
	{
		float frameDuration;
		Animation animation;

	} m_animation;
};

