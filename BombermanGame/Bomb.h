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
	Bomb(const float playerXPosition, const float playerYPosition, const uint16_t& radius, const float trigger);

public:
	uint16_t GetExplosionRadius() const;
	const sf::RectangleShape& GetBombShape() const;
	bool GetBombStatus() const;
	bool GetExplosionShow() const;
	void SetExplosionShow(bool explosionFlag);
	void SetBombStatus(bool status);

public:
	void Update(float elapsedTime);

private:
	void Explode();
	struct AnimationInfo
	{
		Animation anim;
		float frameDuration;
	}m_animation;

private:
	bool m_bombExploded = false;
	uint16_t m_radius = 0;
	float m_triggeredTime = 0;
	sf::RectangleShape m_bombShape;
	sf::Texture m_bombTexture;
	const float m_tickingTime = 2;
	bool m_explosionShowed = false;
};