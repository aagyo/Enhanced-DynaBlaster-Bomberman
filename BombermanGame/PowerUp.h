#pragma once
#include "PowerUpType.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"

class PowerUp
{
public:
	PowerUp(const sf::Vector2f& position);
	~PowerUp() = default;
	PowerUp(const PowerUp& other) = default;
	PowerUp(PowerUp&& other) noexcept = default;
	PowerUp& operator=(const PowerUp& other) = default;
	PowerUp& operator=(PowerUp&& other) noexcept = default;

public:
	PowerType GetPowerType();
	sf::RectangleShape GetShape();
	bool GetIsVisible();

public:
	void SetPowerType(const PowerType& type);
	void SetIsVisible(bool state);
	void SetTextureRect(const sf::IntRect&);

public:
	void CreateRandomPowerUp();

protected:
	const float m_tileSize = 48.f;

private:
	sf::RectangleShape m_powerUpShape;
	PowerType m_powerType;
	sf::Texture m_powerTexture;
	bool isVisible;
};