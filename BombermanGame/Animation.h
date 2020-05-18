#pragma once
#include <vector>
#include <array>

#include <SFML/Graphics/Rect.hpp>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	Animation(const Animation& other) = default;
	Animation(Animation&& other) noexcept = default;
	Animation& operator=(const Animation& other) = default;
	Animation& operator=(Animation&& other) noexcept = default;

public:
	Animation(const sf::IntRect& frame, uint16_t numberOfFrames);

public:
	void Update(float currentTime, float animationTime);
	void UpdateExplosion(float currentTime, float animationTime);
	std::vector<sf::IntRect> GetExplosionsFrames(const std::array<uint16_t, 4>& animationFrameFrequency, uint16_t radius);

public:
	sf::IntRect GetFrame() const;
	uint16_t GetCurrentFrame() const;
	uint16_t GetNumberOfFrames() const;
	uint16_t GetCurrentExplosionFrame() const;
	float GetTimeOfLastUpdate() const;

public:
	void SetFirstFrame(sf::IntRect& frame);
	void SetFrame(sf::IntRect& frame);
	void SetNumberOfFrames(uint16_t numberOfFrames);

private:
	sf::IntRect m_firstFrame;
	sf::IntRect m_frame;
	uint16_t m_currentExplosionFrame = -1;
	uint16_t m_currentFrame = 0;
	uint16_t m_numberOfFrames;
	float m_timeOfLastUpdate = 0.f;
};