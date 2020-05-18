#include "Portal.h"

Portal::Portal(const sf::Vector2f& position) : m_portalBlock(sf::Vector2f(48,48))
{
	m_portalBlock.setPosition(position);
	m_portalTexture.loadFromFile("../_external/sprites/portal.png");
	m_portalBlock.setTexture(&m_portalTexture);


	// sterge aici
	m_animation.anim = Animation(sf::IntRect(0, 0, 48, 48),4);
}

sf::RectangleShape Portal::GetShape() const
{
	return m_portalBlock;
}

void Portal::SetIsVisible(bool state)
{
	m_isVisible = state;
}

sf::Vector2f Portal::GetPortalPosition() {

	return m_portalBlock.getPosition();
}

void Portal::Update(float elapsedTime)
{
	m_animation.anim.Update(elapsedTime, m_animation.frameDuration);
	m_portalBlock.setTextureRect(m_animation.anim.GetFrame());
}


