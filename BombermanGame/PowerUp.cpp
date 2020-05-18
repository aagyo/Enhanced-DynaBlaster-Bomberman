#include "PowerUp.h"

#include <random>

PowerUp::PowerUp(const sf::Vector2f& position) : m_powerUpShape(sf::Vector2f(m_tileSize, m_tileSize))
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
	const std::uniform_int_distribution<> powerNumber(3, static_cast<uint16_t>(PowerType::Count) - 1);

	uint16_t randomNumber = powerNumber(gen);

	const std::uniform_int_distribution<> probability(0, static_cast<uint16_t>(1));

	const uint16_t superPowerUpProbability = probability(gen);

	if (superPowerUpProbability == 1)
	{
		const std::uniform_int_distribution<> numberOfSuperPower(1, static_cast<uint16_t>(3));
		uint16_t superPowerUp = numberOfSuperPower(gen);

		m_powerType = static_cast<PowerType>(superPowerUp);
		m_powerUpShape.setTextureRect(sf::IntRect((superPowerUp * static_cast<uint16_t>(m_tileSize)), 0, static_cast<uint16_t>(m_tileSize),
			static_cast<uint16_t>(m_tileSize)));
	}
	else 
	{
		m_powerType = static_cast<PowerType>(randomNumber);
		m_powerUpShape.setTextureRect(sf::IntRect(static_cast<uint16_t>(randomNumber * static_cast<uint16_t>(m_tileSize)), 0, static_cast<uint16_t>(m_tileSize),
			static_cast<uint16_t>(m_tileSize)));
	}
}