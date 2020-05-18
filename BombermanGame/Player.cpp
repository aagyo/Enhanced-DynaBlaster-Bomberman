#include "Player.h"
#include "Bomb.h"
#include <iostream>

Player::Player() : 
	m_playerShape(sf::Vector2f(m_playerHeight, m_playerWidth)),
	m_numberOfLives(3),
	m_maximumNoBombs(4),
	m_radiusStatus(2),
	m_isCollision(true),
	m_playerSpeed(1.2f)
{
	SetStartPosition();

	m_playerTexture.loadFromFile("../_external/sprites/boamberman.png");
	m_deadTexture.loadFromFile("../_external/sprites/dead_animation.png");
	m_playerTexture.setSmooth(true);
	m_playerShape.setTexture(&m_playerTexture);

	m_direction.leftDirection = sf::IntRect(0, 144, 48, 48);
	m_direction.rightDirection = sf::IntRect(0, 96, 48, 48);
	m_direction.upDirection = sf::IntRect(0, 192, 48, 48);
	m_direction.downDirection = sf::IntRect(0, 48, 48, 48);
	m_direction.stayDirection = sf::IntRect(0, 0, 48, 48);
	m_direction.dead = sf::IntRect(0, 0, 48, 48);

	m_animationComponents.animation = Animation(m_direction.stayDirection, 3);

	m_playerShape.setSize(sf::Vector2f(43.f, 43.f));
	
}

void Player::SetDeadAnimation()
{
	m_playerShape.setTexture(&m_deadTexture);
	m_animationComponents.animation = Animation(m_direction.dead, 4);
	m_animationComponents.frameDuration = 3.f / 4;
	m_deadAnimation = true;
}

void Player::SetStartPosition()
{
	m_playerShape.move(m_startPositionCoord, m_startPositionCoord);
}

void Player::SetNumberOfBombs(uint8_t number)
{
	if (m_maximumNoBombs < m_maxStatusNumber)
		m_maximumNoBombs += number;
}

void Player::SetRadius(uint8_t number)
{
	if (m_radiusStatus < m_maxStatusNumber)
		m_radiusStatus += number;
}

void Player::SetLife(uint8_t life)
{
	m_numberOfLives += life;
}

void Player::SetIsCollision(bool status)
{
	m_isCollision = status;
}

void Player::SetPlayerSpeed(float speedAdded)
{
	if (m_playerSpeed < 2.0f)
		m_playerSpeed += speedAdded;
}

void Player::SetIsDead(bool status)
{
	m_isDead = status;
}

float Player::GetPlayerWidth() const
{
	return m_playerWidth;
}

float Player::GetPlayerHeight() const
{
	return m_playerHeight;
}

float Player::GetPositionX() const
{
	return m_playerShape.getPosition().x;
}

float Player::GetPositionY() const
{
	return m_playerShape.getPosition().y;
}

float Player::GetPlayerSpeed() const
{
	return m_playerSpeed;
}

bool Player::GetCanPlaceBomb() const
{
	return m_placeBomb;
}

uint16_t Player::GetMaxNoBombs() const
{
	return m_maximumNoBombs;
}

bool Player::GetIsDead()
{
	return m_isDead;
}

void Player::DeadAnimation(float deltaTime)
{
	if(m_deadAnimation == false)
		SetDeadAnimation();
	if (m_isDead == false) {
		m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());
		if (m_animationComponents.animation.GetCurrentFrame() == 0)
			m_isDead = true;
		m_animationComponents.frameDuration = 3.0f / m_animationComponents.animation.GetNumberOfFrames();
		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());
	}
}

sf::RectangleShape Player::GetPlayerShape() const
{
	return m_playerShape;
}

void Player::SetMaxNoBombs(uint16_t newMaximum)
{
	m_maximumNoBombs = newMaximum;
}

void Player::SetPositionX(float newPositionX)
{
	m_playerShape.setPosition(newPositionX, GetPositionY());
}

void Player::SetPositionY(float newPositionY)
{
	m_playerShape.setPosition(GetPositionX(), newPositionY);
}

void Player::SetCanPlaceBomb(bool isPossible)
{
	m_placeBomb = isPossible;
}

Collider Player::GetCollider()
{
	return Collider(m_playerShape);
}

uint8_t Player::GetRadiusStatus()
{
	return m_radiusStatus;
}

uint8_t Player::GetNumberOfLives()
{
	return m_numberOfLives;
}

bool Player::GetIsCollision()
{
	return m_isCollision;
}

void Player::MovePlayer(float deltaTime)
{
	if (m_isDead == false) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			m_animationComponents.animation.SetFrame(m_direction.leftDirection);

			m_playerShape.move(-m_playerSpeed, 0.0f);

			m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
			m_direction.leftDirection = m_animationComponents.animation.GetFrame();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			m_animationComponents.animation.SetFrame(m_direction.rightDirection);

			m_playerShape.move(m_playerSpeed, 0.0f);

			m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
			m_direction.rightDirection = m_animationComponents.animation.GetFrame();

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			m_animationComponents.animation.SetFrame(m_direction.upDirection);

			m_playerShape.move(0.0f, -m_playerSpeed);

			m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
			m_direction.upDirection = m_animationComponents.animation.GetFrame();

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			m_animationComponents.animation.SetFrame(m_direction.downDirection);

			m_playerShape.move(0.0f, +m_playerSpeed);

			m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
			m_direction.downDirection = m_animationComponents.animation.GetFrame();
		}

		else
		{
			m_animationComponents.animation.SetFrame(m_direction.stayDirection);

			m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
			m_direction.stayDirection = m_animationComponents.animation.GetFrame();
		}

		m_animationComponents.frameDuration = m_timeAnimationPlayer / m_animationComponents.animation.GetNumberOfFrames();

		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());

	}
}