#pragma once
#include "Block.h"
#include "Animation.h"

class Portal
{
public:
	Portal(const sf::Vector2f& position);
	~Portal() = default;
	Portal(const Portal& other) = default;
	Portal(Portal&& other) noexcept = default;
	Portal& operator=(const Portal& other) = default;
	Portal& operator=(Portal&& other) noexcept = default;

public:
	sf::RectangleShape GetShape() const;
	sf::Vector2f GetPortalPosition() const;
	bool GetIsVisible() const;
	
public:
	void SetIsVisible(bool state);

public:
	void Update(float elapsedTime);

protected:
	const float m_tileSize = 48.f;
	const uint16_t m_numberOfFrames = 4;

private:
	sf::Texture m_portalTexture;
	sf::RectangleShape m_portalBlock;
	bool m_isVisible = false;

private:
	struct AnimationInfo
	{
		Animation anim;
		float frameDuration = 0.5f;
		
	}m_animation;
};