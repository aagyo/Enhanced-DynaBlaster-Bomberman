#include "GameBar.h"
#include <string> 
#include <iostream>
GameBar::GameBar() : m_timeFinished(false), m_numberOfSecound(180), elapsedTime(0), m_highScore(0)
{

	m_barTexture.loadFromFile("../_external/sprites/bar.png");
	m_barTexture.setSmooth(true);
	m_bar.setTexture(m_barTexture);
	m_bar.setPosition(0.f, 816.f);

	m_font.loadFromFile("../_external/font/bm.ttf");
	m_lifeText.setString("3");
	m_lifeText.setFont(m_font);
	m_lifeText.setCharacterSize(15);
	m_lifeText.setPosition(162.f, 825.f);

	m_scoreText.setString(std::to_string(m_highScore));
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(18);
	m_scoreText.setPosition(213.f, 824.f);

	m_timeText.setFont(m_font);
	m_timeText.setCharacterSize(25);
	m_timeText.setPosition(440.f, 820.f);

}


void GameBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_bar);
	target.draw(m_lifeText);
	target.draw(m_scoreText);
	target.draw(m_timeText);

}

void GameBar::SetScoreText(uint16_t score)
{
	m_highScore += score;
	m_scoreText.setString(std::to_string(m_highScore));
}

void GameBar::SetTimeText(const std::string& time)
{
	m_timeText.setString(time);
}

void GameBar::SetLifeText(uint16_t lifeNumber)
{
	m_lifeText.setString(std::to_string(lifeNumber));
}

void GameBar::SetElapsedTime(float time)
{
	elapsedTime = time;
}

void GameBar::SetAddTime(uint8_t seconds)
{
	m_numberOfSecound += seconds;
}


void GameBar::CalculateAndCheck()
{
	uint16_t numberOfSeconds = m_numberOfSecound;

	if (m_timeFinished != true) {

		numberOfSeconds -= static_cast<uint8_t>(elapsedTime);

		if (numberOfSeconds == 0)
		{
			m_timeFinished = true;

		}

		if (numberOfSeconds % 60 < 10)
		{
			m_timeText.setString(std::to_string(numberOfSeconds / 60) + ":0" + std::to_string(numberOfSeconds % 60));
		}
		else
		{
			m_timeText.setString(std::to_string(numberOfSeconds / 60) + ":" + std::to_string(numberOfSeconds % 60));
		}
		numberOfSeconds = 70;

	}

}

bool GameBar::GetTimeFinished()
{
	return m_timeFinished;
}
