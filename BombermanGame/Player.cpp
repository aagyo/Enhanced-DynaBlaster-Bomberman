#include "Player.h"
#include "Bomb.h"
#include "Window.h"
#include <iostream>

Player::Player() : m_playerShape(sf::Vector2f(m_playerHeight, m_playerWidth))/*, indexHeightPlayerOnTile(0) , indexWidthPlayerOnTile(0)*/
{
	SetStartPosition();

	m_playerTexture.loadFromFile("../_external/sprites/boamberman.png");
	m_playerTexture.setSmooth(true);
	m_playerShape.setTexture(&m_playerTexture);
}

void Player::SetStartPosition() 
{
	m_playerShape.move(m_startPositionCoord, m_startPositionCoord);
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
	return m_canPlaceBomb;
}

sf::RectangleShape Player::GetPlayerShape() const
{
	return m_playerShape;
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
	m_canPlaceBomb = isPossible;
}

Collider Player::GetCollider()
{
	return Collider(m_playerShape);
}

void Player::MovePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_playerShape.move(-m_playerSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_playerShape.move(m_playerSpeed, 0.0f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_playerShape.move(0.00f, -m_playerSpeed);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_playerShape.move(0.0f, +m_playerSpeed);

	}
}