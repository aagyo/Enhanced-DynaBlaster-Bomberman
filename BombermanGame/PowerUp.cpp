#include "PowerUp.h"
#include <random>
#include <iostream>

PowerUp::PowerUp(const sf::Vector2f& position) : m_powerUpShape(sf::Vector2f(48.f,48.f))
{
	m_powerUpShape.setPosition(position);
	m_powerTexture.loadFromFile("../_external/sprites/powerups.png");
	m_powerUpShape.setTexture(&m_powerTexture);

	isVisible = true;
	m_powerType = PowerType::Count;
}

PowerType PowerUp::GetPowerType()
{
	return m_powerType;
}

bool PowerUp::GetIsVisible()
{
	return isVisible;
}

sf::RectangleShape PowerUp::GetShape()
{
	return m_powerUpShape;
}

void PowerUp::SetPowerType(const PowerType& type )
{
	m_powerType = type;
}

void PowerUp::SetIsVisible(bool state)
{
	isVisible = state;
}

void PowerUp::SetTextureRect(const sf::IntRect& textureRect)
{
	m_powerUpShape.setTextureRect(textureRect);
}

void PowerUp::CreateRandomPowerUp()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> powerNumber(4, static_cast<uint16_t>(PowerType::Count) - 1);

	uint16_t randomNumber = powerNumber(gen);

	std::uniform_int_distribution<> probability(0, static_cast<uint16_t>(1000));

	uint16_t superPowerUpProbability = probability(gen);

	std::cout << superPowerUpProbability << "\n";

	if (superPowerUpProbability == 1000)
	{
		std::uniform_int_distribution<> numberOfSuperPower(1, static_cast<uint16_t>(3));
		uint16_t superPowerUp = numberOfSuperPower(gen);

		m_powerType = static_cast<PowerType>(superPowerUp);
		m_powerUpShape.setTextureRect(sf::IntRect(superPowerUp * 48, 0, 48, 48));


	}
	else 
	{
		m_powerType = static_cast<PowerType>(randomNumber);
		m_powerUpShape.setTextureRect(sf::IntRect(randomNumber * 48, 0, 48, 48));
	}
}
