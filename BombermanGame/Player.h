#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

class Player
{
public:
	Player();
	~Player() = default;
	Player(const Player& other) = default;
	Player(Player&& other) noexcept = default;
	Player& operator=(const Player& other) = default;
	Player& operator=(Player&& other) noexcept = default;

public:
	sf::RectangleShape GetPlayerShape() const;
	float GetPlayerWidth() const;
	float GetPlayerHeight() const;
	float GetPositionX() const;
	float GetPositionY() const;
	float GetPlayerSpeed() const;
	bool GetCanPlaceBomb() const;
	Collider GetCollider();

public:
	void SetMaxNoBombs(uint16_t newMaximum);
	void SetPositionX(float newPositionX);
	void SetPositionY(float newPositionY);
	void SetCanPlaceBomb(bool isPossible);

public:
	void MovePlayer(float deltaTime);

private:
	void SetDeadAnimation();
	void SetStartPosition();

public:
	void SetNumberOfBombs(uint8_t number);
	void SetRadius(uint8_t number);
	void SetLife(uint8_t number);
	void SetIsCollision(bool status);
	void SetPlayerSpeed(float speedAdded);
	void SetIsDead(bool status);

	uint8_t GetRadiusStatus();
	uint8_t GetNumberOfLives();
	bool GetIsCollision();
	uint16_t GetMaxNoBombs() const;
	bool GetIsDead();
	
	void DeadAnimation(float deltaTime);

private:
	const float m_startPositionCoord = 48.f;
	const float m_playerHeight = 45.f;
	const float m_playerWidth = 45.f;
	const float m_timeAnimationPlayer = 0.6f;

private:
	bool m_placeBomb = true;
	bool m_isDead = false;
	bool m_deadAnimation = false;

private:
	sf::RectangleShape m_playerShape;
	sf::RectangleShape m_secondaryShape;
	sf::Texture m_playerTexture;
	sf::Texture m_deadTexture;

private:
	struct AnimationComponents
	{
		Animation animation;
		float frameDuration;

	}m_animationComponents;

private:
	struct PlayerDirectionAnimation
	{
		sf::IntRect leftDirection;
		sf::IntRect rightDirection;
		sf::IntRect upDirection;
		sf::IntRect downDirection;
		sf::IntRect stayDirection;
		sf::IntRect dead;

	}m_direction;


private:
	uint8_t m_radiusStatus;
	uint16_t m_maximumNoBombs;
	uint8_t m_numberOfLives;
	float m_playerSpeed;
	bool m_isCollision;
	const uint8_t m_maxStatusNumber = 9;
};