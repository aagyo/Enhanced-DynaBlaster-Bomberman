#pragma once
#include "Collider.h"
#include "EnemyDirection.h"
#include "Animation.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy() = default;
	Enemy(const Enemy& other) = default;
	Enemy(Enemy&& other) noexcept = default;
	Enemy& operator=(const Enemy& other) = default;
	Enemy& operator=(Enemy&& other) noexcept = default;

public:
	Collider GetCollider();
	Direction GetDirection();
	Direction GetLastDirection();
	sf::RectangleShape GetShape() const;
	float GetPositionX() const;
	float GetPositionY() const;
	float GetLastTimeMoving() const;
	bool GetWallHitted() const;
	void UpdateAnimation(const float elapsedTime);

public:
	void SetLastTimeMoving(float elapsedTime);
	void SetPosition(const sf::Vector2f& position);
	void SetDirection(Direction direction);
	void SetLastDirection(Direction direction);
	void SetWallHitted(bool status);

public:
	struct AnimationComponents
	{
		Animation animation;
		float frameDuration;

	}m_animationComponents;

protected:
	const float m_tileSize = 48.f;

private:
	sf::RectangleShape m_enemyShape;
	sf::Texture m_texture;
	Direction m_direction = Direction::UP;
	Direction m_lastDirection = Direction::UP;
	float m_animationDuration = 1.0f;
	uint8_t m_numberOfFrames = 4;
	float m_lastTimeMoving;
	bool m_wallHitted = true;
};