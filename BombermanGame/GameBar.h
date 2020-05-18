#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class GameBar : public sf::Drawable, public sf::Transformable
{
public:
	GameBar();
	~GameBar() = default;
	GameBar(const GameBar& other) = default;
	GameBar(GameBar&& other) noexcept = default;
	GameBar& operator=(const GameBar& other) = default;
	GameBar& operator=(GameBar&& other) noexcept = default;

public:
	bool GetTimeFinished() const;
	
public:
	void SetScoreText(int score);
	void SetLifeText(uint16_t lifeNumber);
	void SetAddTime(uint16_t seconds);
	void SetTimeText(const std::string& time);
	void SetElapsedTime(float time);
	void CalculateAndCheck();
	void SetHighScore(int highscore);
	int GetHighScore();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Texture m_barTexture;
	sf::Sprite m_bar;
	sf::Font m_font;
	sf::Text m_lifeText;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Color color;
	uint16_t m_numberOfSecond;
	uint32_t m_highScore;
	float elapsedTime;
	bool m_timeFinished;
};