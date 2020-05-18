#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(sf::Texture* texture, const sf::Vector2i& imageCount) :
	m_imageCount(imageCount)
{
	m_totalTime = 0;
	m_currentImage.x = 0;

	uVRect.width = static_cast<int>(texture->getSize().x) / imageCount.x;
	uVRect.height = static_cast<int>(texture->getSize().y) / imageCount.y;
}

void AnimationPlayer::Update(uint16_t row, float deltaTime, bool faceRight)
{
	m_currentImage.y = row;
	m_totalTime += deltaTime;

	if (m_totalTime >= deltaTime)
	{
		m_totalTime -= 1.f;
		m_currentImage.x++;

		if (m_currentImage.x >= m_imageCount.x)
		{
			m_currentImage.x = 0;
		}
	}

	uVRect.top = m_currentImage.y * uVRect.height;

	if (faceRight)
	{
		uVRect.left = m_currentImage.x * uVRect.width;
		uVRect.width = abs(uVRect.width);
	}
	else
	{
		uVRect.left = (m_currentImage.x + 1) * abs(uVRect.width);
		uVRect.width = -abs(uVRect.width);
	}
}