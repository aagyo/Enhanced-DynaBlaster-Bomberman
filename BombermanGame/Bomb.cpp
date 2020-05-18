#include "Bomb.h"
#include "Animation.h"

Bomb::Bomb(const float playerXPosition, const float playerYPosition, const uint16_t radius, const float trigger) :
	m_radius(radius), m_triggeredTime(trigger), m_bombShape(sf::Vector2f(m_tileSize, m_tileSize))
{
	m_bombShape.setPosition(playerXPosition, playerYPosition);
	m_bombTexture.loadFromFile("../_external/sprites/bomb.png");
	m_bombTexture.setSmooth(true);
	m_bombShape.setTexture(&m_bombTexture);

	m_animation.anim = Animation(sf::IntRect(0, 0, static_cast<uint16_t>(m_tileSize), static_cast<uint16_t>(m_tileSize)), m_numberOfFrames);
	m_animation.frameDuration = m_tickingTime / static_cast<float>(m_animation.anim.GetNumberOfFrames());
	m_bombShape.setTextureRect(m_animation.anim.GetFrame());
}

void Bomb::Update(float elapsedTime)
{
	m_animation.anim.Update(elapsedTime, m_animation.frameDuration);
	m_bombShape.setTextureRect(m_animation.anim.GetFrame());

	if (elapsedTime - m_triggeredTime >= m_tickingTime)
	{
		Explode();
	}
}

uint16_t Bomb::GetExplosionRadius() const
{
	return m_radius;
}

sf::RectangleShape Bomb::GetBombShape() const
{
	return m_bombShape;
}

bool Bomb::GetBombStatus() const
{
	return m_bombExploded;
}

bool Bomb::GetExplosionShow() const
{
	return m_explosionShowed;
}

void Bomb::SetExplosionShow(bool explosionFlag)
{
	m_explosionShowed = explosionFlag;
}

void Bomb::SetBombStatus(bool status)
{
	m_bombExploded = status;
}

void Bomb::Explode()
{
	m_bombExploded = true;
}