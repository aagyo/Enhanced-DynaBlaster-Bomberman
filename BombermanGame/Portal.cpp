#include "Portal.h"

Portal::Portal(const sf::Vector2f& position) : m_portalBlock(sf::Vector2f(m_tileSize, m_tileSize))
{
	m_portalBlock.setPosition(position);
	m_portalTexture.loadFromFile("../_external/sprites/portal.png");
	m_portalBlock.setTexture(&m_portalTexture);
	
	m_animation.anim = Animation(sf::IntRect(0, 0, static_cast<uint16_t>(m_tileSize), static_cast<uint16_t>(m_tileSize)), m_numberOfFrames);
}

sf::RectangleShape Portal::GetShape() const
{
	return m_portalBlock;
}

void Portal::SetIsVisible(bool state)
{
	m_isVisible = state;
}

bool Portal::GetIsVisible() const
{
	return m_isVisible;
}

sf::Vector2f Portal::GetPortalPosition() const
{
	return m_portalBlock.getPosition();
}

void Portal::Update(float elapsedTime)
{
	m_animation.anim.Update(elapsedTime, m_animation.frameDuration);
	m_portalBlock.setTextureRect(m_animation.anim.GetFrame());
}