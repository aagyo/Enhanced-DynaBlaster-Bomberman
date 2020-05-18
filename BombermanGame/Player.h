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
	uint16_t GetMaxNoBombs() const;
	Collider GetCollider();
	static uint16_t GetNumberOfLives();

public:
	void SetMaxNoBombs(uint16_t newMaximum);
	void SetPositionX(float newPositionX);
	void SetPositionY(float newPositionY);
	void SetCanPlaceBomb(bool isPossible);
	static void SetNumberOfLives(uint16_t life);

public:
	void MovePlayer(float deltaTime);

private:
	void SetStartPosition();

private:
	const float m_startPositionCoord = 48.f;
	const float m_playerSpeed = 1.8f;
	const float m_playerHeight = 45.f;
	const float m_playerWidth = 45.f;
	const float m_timeAnimationPlayer = 0.6f;

private:
	bool m_placeBomb = true;
	static uint16_t m_numberOfLives;
	uint16_t m_maximumNoBombs = 3;

private:
	sf::RectangleShape m_playerShape;
	sf::RectangleShape m_secondaryShape;
	sf::Texture m_playerTexture;

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

	}m_direction;
};