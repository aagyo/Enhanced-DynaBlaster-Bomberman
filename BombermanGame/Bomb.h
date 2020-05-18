#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Bomb
{
public:
	Bomb() = default;
	~Bomb() = default;
	Bomb(const Bomb& other) = default;
	Bomb(Bomb&& other) noexcept = default;
	Bomb& operator=(Bomb&& other) noexcept = default;

public:
	Bomb(const float playerXPosition, const float playerYPosition, const uint16_t radius, const float trigger);

public:
	uint16_t GetExplosionRadius() const;
	const sf::RectangleShape& GetBombShape() const;
	bool GetBombStatus() const;

public:
	void Update(float elapsedTime);
	void operator=(const Bomb& bomb);

private:
	void Explode();

	struct AnimationInfo
	{
		Animation anim;
		float frameDuration;

	}m_animation;

private:
	bool m_bombExploded = false;
	float m_triggeredTime = 0;
	uint16_t m_radius = 2;
	sf::RectangleShape m_bombShape;
	sf::Texture m_bombTexture;
	const float m_tickingTime = 2;
};