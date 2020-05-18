#pragma once
#include "SFML/Graphics.hpp"
class GameBar : public sf::Drawable, public sf::Transformable
{
public:

	GameBar();
	~GameBar() = default;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void SetScoreText(uint16_t score);
	void SetTimeText(const std::string& time);
	void SetLifeText(uint16_t lifeNumber);
	void SetElapsedTime(float time);
	void SetAddTime(uint8_t seconds);
	void CalculateAndCheck();

	bool GetTimeFinished();

public:
	sf::Texture m_barTexture;
	sf::Sprite m_bar;
	sf::Font m_font;
	sf::Text m_lifeText;
	sf::Text m_scoreText;
	sf::Text m_timeText;

	bool m_timeFinished;
	float elapsedTime;
	uint16_t m_numberOfSecound;
	int m_highScore;

	sf::Color color;
};

