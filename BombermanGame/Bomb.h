#pragma once
#include "Animation.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class Bomb
{
public:
	Bomb(const float playerXPosition, const float playerYPosition, const uint16_t radius, const float trigger);
	~Bomb() = default;
	Bomb(const Bomb& other) = default;
	Bomb(Bomb&& other) noexcept = default;
	Bomb& operator=(const Bomb& other) = default;
	Bomb& operator=(Bomb&& other) noexcept = default;

public:
	uint16_t GetExplosionRadius() const;
	bool GetBombStatus() const;
	bool GetExplosionShow() const;
	sf::RectangleShape GetBombShape() const;

public:
	void SetExplosionShow(bool explosionFlag);
	void SetBombStatus(bool status);

public:
	void Update(float elapsedTime);

protected:
	const float m_tileSize = 48.f;

private:
	void Explode();
	struct AnimationInfo
	{
		Animation anim;
		float frameDuration;
		
	}m_animation;

private:
	const uint16_t m_radius = 0;
	const uint16_t m_numberOfFrames = 5;
	const float m_triggeredTime = 0.f;
	const float m_tickingTime = 2.f;
	sf::RectangleShape m_bombShape;
	sf::Texture m_bombTexture;
	bool m_bombExploded = false;
	bool m_explosionShowed = false;
};