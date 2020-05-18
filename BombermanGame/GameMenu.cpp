#include "GameMenu.h"

GameMenu::GameMenu(float width, float height)
{
	if (!m_font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	m_menu[0].setFont(m_font);
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setString("Play");
	m_menu[0].setPosition(sf::Vector2f(width / 2, height / 3 * 1));

	m_menu[1].setFont(m_font);
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setString("EXIT");
	m_menu[1].setPosition(sf::Vector2f(width / 2, height / 3 * 2));
	m_selectedItemIndex = 0;
}
void GameMenu::draw(const sf::RenderWindow& window) const
{
	for (int i = 0; i < 2; i++)
	{
		//window.draw(m_menu[i]);
	}
}

void GameMenu::MoveUp()
{
	if (m_selectedItemIndex - 1 >= 0)
	{
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
		m_selectedItemIndex--;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Red);
	}
}