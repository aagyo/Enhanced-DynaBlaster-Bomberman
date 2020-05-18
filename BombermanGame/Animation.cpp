#include "Animation.h"

Animation::Animation(const sf::IntRect& frame, uint16_t numberOfFrames) :
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
		
		if (m_currentFrame >= m_numberOfFrames) 
		{
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

std::vector<sf::IntRect> Animation::GetExplosionsFrames(const std::array<uint16_t, 4>& animationFrameFrequency, uint16_t radius)
{
	const uint16_t firstFramePos = 0;
	const uint16_t secondFramePos = 1;
	const uint16_t thirdFramePos = 2;
	const uint16_t fourthFramePos = 3;
	const uint16_t fifthFramePos = 4;
	const uint16_t sixthFramePos = 5;
	const uint16_t seventhFramePos = 6;
	
	std::vector<sf::IntRect> explosionFrames;	
	uint16_t frameUp = animationFrameFrequency[thirdFramePos], frameDown = animationFrameFrequency[fourthFramePos], frameRight = animationFrameFrequency[secondFramePos], frameLeft = animationFrameFrequency[firstFramePos];
	
	while ((frameUp + frameDown + frameLeft + frameRight) != 0)
	{
		if (frameUp != 0)
		{
			m_frame.left = m_firstFrame.left + secondFramePos * m_frame.width;
			explosionFrames.push_back(m_frame);
			frameUp--;
		}

		else if (frameUp == 0 && frameDown != 0)
		{
			m_frame.left = m_firstFrame.left + secondFramePos * m_frame.width;
			explosionFrames.push_back(m_frame);
			frameDown--;
		}

		else if (frameDown == 0 && frameRight != 0)
		{
			m_frame.left = m_firstFrame.left + thirdFramePos * m_frame.width;
			explosionFrames.push_back(m_frame);
			frameRight--;
		}

		else if (frameRight == 0 && frameLeft != 0)
		{
			m_frame.left = m_firstFrame.left + thirdFramePos * m_frame.width;
			explosionFrames.push_back(m_frame);
			frameLeft--;
		}
	}
	
	if (animationFrameFrequency[thirdFramePos] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + fourthFramePos * m_frame.width;
 		explosionFrames.at(animationFrameFrequency[thirdFramePos] - 1) = m_frame;
	}
	
	if (animationFrameFrequency[fourthFramePos] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + fifthFramePos * m_frame.width;
		explosionFrames.at(animationFrameFrequency[thirdFramePos] + animationFrameFrequency[fourthFramePos] - 1) = m_frame;
	}
	
	if (animationFrameFrequency[secondFramePos] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + sixthFramePos * m_frame.width;
		explosionFrames.at(animationFrameFrequency[secondFramePos] + animationFrameFrequency[thirdFramePos] + animationFrameFrequency[fourthFramePos] - 1) = m_frame;
	}
	
	if (animationFrameFrequency[firstFramePos] - radius == 0)
	{
		m_frame = m_firstFrame;
		m_frame.left = m_firstFrame.left + seventhFramePos * m_frame.width;
		explosionFrames.at(animationFrameFrequency[firstFramePos] + animationFrameFrequency[secondFramePos] + animationFrameFrequency[thirdFramePos] + animationFrameFrequency[fourthFramePos] - 1) = m_frame;
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