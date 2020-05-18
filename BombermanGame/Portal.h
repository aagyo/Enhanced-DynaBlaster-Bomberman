#pragma once
#include "Block.h"
#include "Animation.h"

class Portal
{
public:

	Portal() = default;
	Portal(const sf::Vector2f& position);
	Portal& operator=(const Portal& other) = default;
	Portal& operator=(Portal&& other) noexcept = default;
	~Portal() = default;


public:
	sf::RectangleShape GetShape() const;
	void SetIsVisible(bool state);
	bool GetIsVisible() { return m_isVisible; };
	void Update(float elapsedTime);
	sf::Vector2f GetPortalPosition();

private:
	sf::Texture m_portalTexture;
	sf::RectangleShape m_portalBlock;

	// modify here to see portal
	bool m_isVisible = false;

	struct AnimationInfo
	{
		Animation anim;
		float frameDuration = 0.5;
	}m_animation;
};

