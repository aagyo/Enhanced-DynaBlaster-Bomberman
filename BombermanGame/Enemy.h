#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "EnemyDirection.h"
#include "Block.h"
#include "EnemyDirection.h"
#include "Animation.h"

class Enemy
{
public:

	Enemy();
	~Enemy() = default;

	Collider GetCollider();
	sf::RectangleShape GetShape() const;
	float GetPositionX() const;
	float GetPositionY() const;
	float GetLastTimeMoving() const;

	void SetLastTimeMoving(float elapsedTime);

	void SetPosition(const sf::Vector2f& position);
	void UpdateAnimation(const float elapsedTime);

	Direction GetDirection();
	void SetDirection(Direction direction);

	Direction GetLastDirection();
	void SetLastDirection(Direction direction);

	bool GetWallHitted();
	void SetWallHitted(bool status);

public:
	struct AnimationComponents
	{
		Animation animation;
		float frameDuration;

	}m_animationComponents;

private:

	sf::RectangleShape m_enemyShape;
	sf::Texture m_texture;
	float m_lastTimeMoving;
	float m_animationDuration = 1.0f;
	uint8_t m_numberOfFrames = 4;

	Direction m_direction = Direction::UP;
	Direction m_lastDirection = Direction::UP;
	bool m_wallHitted = true;


private:
	float m_speed;
};

