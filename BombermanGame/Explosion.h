#pragma once
#include "Animation.h"
#include "Map.h"

#include <array>
#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"

class Explosion
{
public:
	Explosion(const sf::Vector2f& bombPosition, const uint16_t radius, Map* m_map);
	~Explosion() = default;
	Explosion(const Explosion& other) = default;
	Explosion(Explosion&& other) noexcept = default;
	Explosion& operator=(const Explosion& other) = default;
	Explosion& operator=(Explosion&& other) noexcept = default;

public:
	void Update(float deltaTime, sf::RenderWindow& window);

public:
	sf::RectangleShape GetExplosionShape();
	bool GetExplosionState();

protected:
	const float m_tileSize = 48.f;

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
	const uint16_t m_numberOfFrames = 4;
	uint16_t m_currentState = 5;
	uint16_t m_radius;
	bool m_explosionNotFinished = true;
	bool m_fireBlockMark = false;
	std::array<uint16_t, 4> m_posFrequency;
	std::vector<sf::Vector2f> m_emptyBlocksLocation;
	sf::RectangleShape m_explosionShape;
	sf::Texture m_explosionTexture;
	sf::Vector2f m_center;
};