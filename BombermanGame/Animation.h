#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	Animation(const sf::IntRect frame, uint16_t numberOfFrames);

public:
	void Update(float currentTime, float animationTime);

public:
	sf::IntRect GetFrame() const;
	uint16_t GetNumberOfFrames() const;
	float GetTimeOfLastUpdate() const;

private:
	sf::IntRect m_firstFrame;
	sf::IntRect m_frame;
	uint16_t m_currentFrame = 0;
	uint16_t m_numberOfFrames;
	float m_timeOfLastUpdate = 0;
	float m_frameDuration = 0;

};