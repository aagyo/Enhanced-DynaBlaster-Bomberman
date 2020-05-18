#include "Enemy.h"

Enemy::Enemy() : m_lastTimeMoving(0)
{
	m_texture.loadFromFile("../_external/sprites/enemy.png");
	m_enemyShape.setSize(sf::Vector2f(48, 48.f));
	m_enemyShape.setTexture(&m_texture);
	m_enemyShape.setTextureRect(sf::IntRect(0, 0, 48, 48));
	m_animationComponents.animation = Animation(sf::IntRect(0, 0, 48, 48), m_numberOfFrames);
	m_animationComponents.frameDuration = m_animationDuration / m_numberOfFrames;
}


Collider Enemy::GetCollider()
{
	return Collider(m_enemyShape);
}

sf::RectangleShape Enemy::GetShape() const
{
	return m_enemyShape;
}

float Enemy::GetPositionX() const
{
	return m_enemyShape.getPosition().x;
}

float Enemy::GetPositionY() const
{
	return m_enemyShape.getPosition().y;
}

float Enemy::GetLastTimeMoving() const
{
	return m_lastTimeMoving;
}


void Enemy::SetLastTimeMoving(float elapsedTime)
{
	m_lastTimeMoving = elapsedTime;
}

void Enemy::SetPosition(const sf::Vector2f& position)
{
	m_enemyShape.setPosition(position);
}

void Enemy::UpdateAnimation(const float elapsedTime)
{
	m_animationComponents.animation.Update(elapsedTime, m_animationComponents.frameDuration);
	m_enemyShape.setTextureRect(m_animationComponents.animation.GetFrame());
}

void Enemy::SetDirection(Direction direction)
{
	m_direction = direction;
}

Direction Enemy::GetLastDirection()
{
	return m_lastDirection;
}

void Enemy::SetLastDirection(Direction direction)
{
	m_lastDirection = direction;
}

bool Enemy::GetWallHitted()
{
	return m_wallHitted;
}

void Enemy::SetWallHitted(bool status)
{
	m_wallHitted = status;
}

Direction Enemy::GetDirection()
{
	return m_direction;
}


