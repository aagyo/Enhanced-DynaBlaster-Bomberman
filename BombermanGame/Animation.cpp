#include "Animation.h"
#include <array>

Animation::Animation(const sf::IntRect frame, uint16_t numberOfFrames) :
	m_firstFrame(frame), m_frame(frame), m_numberOfFrames(numberOfFrames)
{
	//empty
}

void Animation::Update(float currentTime, float animationTime)
{
	if (currentTime - m_timeOfLastUpdate >= animationTime)
	{
		m_frame.left = m_firstFrame.left + m_currentFrame * m_frame.width;
		++m_currentFrame;
		if (m_currentFrame >= m_numberOfFrames) {
			m_currentFrame = 0;
		}
		m_timeOfLastUpdate = currentTime;
	}
}

void Animation::UpdateExplosion(float currentTime, float animationTime)
{
	if (currentTime - m_timeOfLastUpdate >= animationTime)
	{
		++m_currentExplosionFrame;
		m_timeOfLastUpdate = currentTime;
	}
}

std::vector<sf::IntRect> Animation::GetExplosionsFrames(std::array<int, 4>& frequency, uint16_t& radius)
{
	std::vector<sf::IntRect> explosionFrames;
	int fu = frequency[2], fd = frequency[3], fr = frequency[1], fl = frequency[0];
	while ((fu + fd + fl + fr) != 0)
	{
		if (fu != 0)
		{
			m_frame.left = m_firstFrame.left + 1 * m_frame.width;
			explosionFrames.push_back(m_frame);
			fu--;
		}

		else if (fu == 0 && fd != 0)
		{
			m_frame.left = m_firstFrame.left + 1 * m_frame.width;
			explosionFrames.push_back(m_frame);
			fd--;
		}

		else if (fd == 0 && fr != 0)
		{
			m_frame.left = m_firstFrame.left + 2 * m_frame.width;
			explosionFrames.push_back(m_frame);
			fr--;
		}

		else if (fr == 0 && fl != 0)
		{
			m_frame.left = m_firstFrame.left + 2 * m_frame.width;
			explosionFrames.push_back(m_frame);
			fl--;
		}
	}
	if (frequency[2] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + 3 * m_frame.width;
 		explosionFrames.at(frequency[2] - 1) = m_frame;
	}
	if (frequency[3] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + 4 * m_frame.width;
		explosionFrames.at(frequency[2] + frequency[3] - 1) = m_frame;
	}
	if (frequency[1] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + 5 * m_frame.width;
		explosionFrames.at(frequency[1] + frequency[2] + frequency[3] - 1) = m_frame;
	}
	if (frequency[0] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + 6 * m_frame.width;
		explosionFrames.at(frequency[0] + frequency[1] + frequency[2] + frequency[3] - 1) = m_frame;
	}

	return explosionFrames;
}

sf::IntRect Animation::GetFrame() const
{
	return m_frame;
}

uint16_t Animation::GetCurrentFrame() const
{
	return m_currentFrame;
}

uint16_t Animation::GetNumberOfFrames() const
{
	return m_numberOfFrames;
}

float Animation::GetTimeOfLastUpdate() const
{
	return m_timeOfLastUpdate;
}

uint16_t Animation::GetCurrentExplosionFrame() const
{
	return m_currentExplosionFrame;
}

void Animation::SetFirstFrame(sf::IntRect& frame)
{
	m_firstFrame = frame;
}

void Animation::SetFrame(sf::IntRect& frame)
{
	m_frame = frame;
}

void Animation::SetNumberOfFrames(uint16_t numberOfFrames)
{
	m_numberOfFrames = numberOfFrames;
}
