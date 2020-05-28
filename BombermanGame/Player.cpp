#include "Player.h"
#include "Bomb.h"

#include <SFML/Window/Keyboard.hpp>

Player::Player() : m_playerShape(sf::Vector2f(m_playerHeight, m_playerWidth)), m_numberOfLives(3), m_maximumNumberOfBombs(2),
	m_radiusStatus(2), m_isCollision(true), m_playerSpeed(1.2f)
{
	SetStartPosition();
	
	m_playerTexture.loadFromFile("../_external/sprites/bomberman.png");
	m_deadTexture.loadFromFile("../_external/sprites/dead_animation.png");
	m_playerTexture.setSmooth(true);
	m_playerShape.setTexture(&m_playerTexture);

	m_direction.leftDirection = sf::IntRect(0, m_tileSize * 3, m_tileSize, m_tileSize);
	m_direction.rightDirection = sf::IntRect(0, m_tileSize * 2, m_tileSize, m_tileSize);
	m_direction.upDirection = sf::IntRect(0, m_tileSize * 4, m_tileSize, m_tileSize);
	m_direction.downDirection = sf::IntRect(0, m_tileSize, m_tileSize, m_tileSize);
	m_direction.stayDirection = sf::IntRect(0, 0, m_tileSize, m_tileSize);
	m_direction.dead = sf::IntRect(0, 0, m_tileSize, m_tileSize);

	m_animationComponents.animation = Animation(m_direction.stayDirection, m_numberOfPlayerFrames);
	m_playerShape.setSize(sf::Vector2f(m_playerWidth, m_playerHeight));
}

void Player::SetDeadAnimation()
{
	m_playerShape.setTexture(&m_deadTexture);
	m_animationComponents.animation = Animation(m_direction.dead, m_numberOfPlayerDeadFrames);
	m_animationComponents.frameDuration = 3.f / 4.f;
	m_deadAnimation = true;
}

void Player::SetStartPosition()
{
	m_playerShape.move(m_startPositionCoord, m_startPositionCoord);
}

void Player::AddNumberOfBombs(uint16_t plusBomb)
{
	if (m_maximumNumberOfBombs < m_maxStatusNumber)
	{
		m_maximumNumberOfBombs += plusBomb;
	}
}

void Player::AddRadius(uint16_t newRadius)
{
	if (m_radiusStatus < m_maxStatusNumber)
	{
		m_radiusStatus += newRadius;
	}
}

void Player::AddLife(uint16_t life)
{
	m_numberOfLives += life;
}

void Player::SetIsCollision(bool status)
{
	m_isCollision = status;
}

void Player::AddPlayerSpeed(float speedAdded)
{
	if (m_playerSpeed < 2.0f)
	{
		m_playerSpeed += speedAdded;
	}
}

void Player::SetIsDead(bool status)
{
	m_isDead = status;
}

void Player::SetNumberOfBombs(uint16_t number)
{
	m_maximumNumberOfBombs = number;
}

void Player::SetRadius(uint16_t number)
{
	m_radiusStatus = number;
}

void Player::SetLife(uint16_t number)
{
	m_numberOfLives = number;
}

void Player::SetPlayerSpeed(float number)
{
	m_playerSpeed = number;
}

void Player::TakeLife()
{
	m_numberOfLives--;
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

uint16_t Player::GetMaxNumberOfBombs() const
{
	return m_maximumNumberOfBombs;
}

bool Player::GetIsDead() const
{
	return m_isDead;
}

void Player::DeadAnimation(float deltaTime)
{
	if (m_deadAnimation == false)
	{
		SetDeadAnimation();
	}
	
	if (m_isDead == false)
	{
		m_animationComponents.animation.Update(deltaTime, m_animationComponents.frameDuration);
		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());
		
		if (m_animationComponents.animation.GetCurrentFrame() == 0)
		{
			m_isDead = true;
		}
		
		m_animationComponents.frameDuration = 3.0f / static_cast<float>(m_animationComponents.animation.GetNumberOfFrames());
		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());
	}
}

sf::RectangleShape Player::GetPlayerShape() const
{
	return m_playerShape;
}

void Player::SetMaxNumberOfBombs(uint16_t newMaximum)
{
	m_maximumNumberOfBombs = newMaximum;
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

uint16_t Player::GetRadiusStatus() const
{
	return m_radiusStatus;
}

uint16_t Player::GetNumberOfLives() const
{
	return m_numberOfLives;
}

bool Player::GetIsCollision() const
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

		m_animationComponents.frameDuration = m_timeAnimationPlayer / static_cast<float>(m_animationComponents.animation.GetNumberOfFrames());
		m_playerShape.setTextureRect(m_animationComponents.animation.GetFrame());
	}
}