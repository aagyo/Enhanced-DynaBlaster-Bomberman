#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	Animation(const sf::IntRect frame, uint16_t numberOfFrames);

public:
	void Update(float currentTime, float animationTime);
	void UpdateExplosion(float currentTime, float animationTime);
	std::vector<sf::IntRect> GetExplosionsFrames(std::array<int, 4>& frequency, uint16_t& radius);

public:
	sf::IntRect GetFrame() const;
	uint16_t GetCurrentFrame() const;
	uint16_t GetNumberOfFrames() const;
	float GetTimeOfLastUpdate() const;
	uint16_t GetCurrentExplosionFrame() const;
	void SetFirstFrame(sf::IntRect& frame);
	void SetFrame(sf::IntRect& frame);
	void SetNumberOfFrames(uint16_t numberOfFrames);

private:
	sf::IntRect m_firstFrame;
	sf::IntRect m_frame;
	int m_currentExplosionFrame = -1;
	uint16_t m_currentFrame = 0;
	uint16_t m_numberOfFrames;
	float m_timeOfLastUpdate = 0;
	float m_frameDuration = 0;
};