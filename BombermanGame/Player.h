#pragma once
#include "Collider.h"
#include "Animation.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

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
	float GetPlayerWidth() const;
	float GetPlayerHeight() const;
	float GetPositionX() const;
	float GetPositionY() const;
	float GetPlayerSpeed() const;
	bool GetCanPlaceBomb() const;
	sf::RectangleShape GetPlayerShape() const;
	Collider GetCollider();
	uint16_t GetRadiusStatus() const;
	uint16_t GetNumberOfLives() const;
	bool GetIsCollision() const;
	uint16_t GetMaxNumberOfBombs() const;
	bool GetIsDead() const;

public:
	void SetPositionX(float newPositionX);
	void SetPositionY(float newPositionY);
	void SetCanPlaceBomb(bool isPossible);
	void SetMaxNumberOfBombs(uint16_t newMaximum);
	void AddNumberOfBombs(uint16_t plusBomb);
	void AddRadius(uint16_t newRadius);
	void AddLife(uint16_t number);
	void SetIsCollision(bool status);
	void AddPlayerSpeed(float speedAdded);
	void SetIsDead(bool status);
	void SetNumberOfBombs(uint16_t number);
	void SetRadius(uint16_t number);
	void SetLife(uint16_t number);
	void SetPlayerSpeed(float number);
	void TakeLife();
	

public:
	void MovePlayer(float deltaTime);
	void DeadAnimation(float deltaTime);

private:
	void SetDeadAnimation();
	void SetStartPosition();

private:
	const float m_startPositionCoord = 48.f;
	const float m_playerHeight = 45.f;
	const float m_playerWidth = 45.f;
	const float m_timeAnimationPlayer = 0.6f;
	const uint16_t m_tileSize = 48;
	const uint16_t m_numberOfPlayerFrames = 3;
	const uint16_t m_numberOfPlayerDeadFrames = 4;

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
	uint16_t m_radiusStatus;
	uint16_t m_maximumNumberOfBombs;
	uint16_t m_numberOfLives;
	const uint16_t m_maxStatusNumber = 9;
	float m_playerSpeed;
	bool m_isCollision;
};