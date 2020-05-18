#pragma once
#include "SFML/Graphics.hpp"
#include "PowerUpType.h"

class PowerUp
{
public:

	PowerUp() = default;
	PowerUp(const sf::Vector2f& position);
	PowerUp& operator=(const PowerUp& other) = default;
	PowerUp& operator=(PowerUp&& other) noexcept = default;
	~PowerUp() = default;

public:

	PowerType GetPowerType();
	bool GetIsVisible();
	sf::RectangleShape GetShape();

public:

	void SetPowerType(const PowerType& type);
	void SetIsVisible(bool state);
	void SetTextureRect(const sf::IntRect&);

public:

	void CreateRandomPowerUp();


private:
	sf::RectangleShape m_powerUpShape;
	PowerType m_powerType;
	sf::Texture m_powerTexture;
	bool isVisible;

};

