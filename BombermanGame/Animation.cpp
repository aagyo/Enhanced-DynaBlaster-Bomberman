#include "Animation.h"

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

sf::IntRect Animation::GetFrame() const
{
	return m_frame;
}

uint16_t Animation::GetNumberOfFrames() const
{
	return m_numberOfFrames;
}

float Animation::GetTimeOfLastUpdate() const
{
	return m_timeOfLastUpdate;
}

void Animation::SetFrame(sf::IntRect& frame)
{
	m_frame = frame;
}