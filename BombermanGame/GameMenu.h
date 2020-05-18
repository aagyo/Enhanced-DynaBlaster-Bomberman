#pragma once
#include "SFML/Graphics.hpp"

class GameMenu
{
public:
	GameMenu() = default;
	~GameMenu() = default;
	GameMenu(const GameMenu& other) = default;
	GameMenu(GameMenu&& other) noexcept = default;
	GameMenu& operator=(const GameMenu& other) = default;
	GameMenu& operator=(GameMenu&& other) noexcept = default;

public:
	GameMenu(float width, float height);

public:
	void draw(const sf::RenderWindow& window) const;
	void MoveUp();
	void MoveDown();

public:
	uint16_t GetPressedItem() const;

private:
	uint16_t m_selectedItemIndex;
	sf::Font m_font;
	sf::Text m_menu[2];
};