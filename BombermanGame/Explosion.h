#pragma once
#include "Animation.h"
#include "Map.h"
#include <array>
#include <vector>


class Explosion
{

public:
	Explosion() = default;
	~Explosion() = default;

public:
	Explosion(const sf::Vector2f& bombPosition, const uint16_t& radius, Map* m_map);
	void Update(float deltaTime, sf::RenderWindow& window);

public:
	sf::RectangleShape GetExplosionShape() const;
	bool GetExplosionState() const;

private:
	void PlaceExplosion();
	void Draw(sf::RenderWindow& window);

private:
	struct AnimationComponents
	{
		Animation animation;
		float frameDuration;

	}m_animationComponents;

	struct BlocksOnDirection
	{
		std::vector<sf::Vector2f> left;
		std::vector<sf::Vector2f> right;
		std::vector<sf::Vector2f> up;
		std::vector<sf::Vector2f> down;
	}m_blockOnDir;

	struct ExplosionStateAnimation
	{
		sf::IntRect firstState;
		sf::IntRect secondState;
		sf::IntRect thirdState;
		sf::IntRect finalState;
	}m_direction;

private:
	Map* m_map;
	uint16_t m_currentState = 5;
	uint16_t m_numberOfFrames = 4;
	std::array<int, 4> m_posFrequency;
	sf::Vector2f m_center;
	uint16_t m_radius;
	std::vector<sf::Vector2f> m_emptyBlocksLocation;
	bool m_explosionNotFinished = true;
	bool m_fireBlockMark = false;
	sf::RectangleShape m_explosionShape;
	sf::Texture m_explosionTexture;

};
