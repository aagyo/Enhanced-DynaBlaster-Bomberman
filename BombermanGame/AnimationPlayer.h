#pragma once
#include "SFML/Graphics/Texture.hpp"

class AnimationPlayer
{
public:
	AnimationPlayer(sf::Texture* texture, const sf::Vector2i& imageCount);
	~AnimationPlayer() = default;
	AnimationPlayer(const AnimationPlayer& other) = default;
	AnimationPlayer(AnimationPlayer&& other) noexcept = default;
	AnimationPlayer& operator=(const AnimationPlayer& other) = default;
	AnimationPlayer& operator=(AnimationPlayer&& other) noexcept = default;

public:
	void Update(uint16_t row, float deltaTime, bool faceRight);

public:
	sf::IntRect uVRect;

private:
	sf::Vector2i m_imageCount;
	sf::Vector2i m_currentImage;
	float m_totalTime;
};