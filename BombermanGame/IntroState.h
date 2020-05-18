#pragma once
#include "State.h"
#include "StateMachine.h"

#include <SFML/Graphics.hpp>

class IntroState : public State
{
public:
	IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

public:
	void Pause() override;
	void Resume() override;
	void Update() override;
	void Draw() override;

private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bg;
	uint16_t m_selectedItemIndex;
	sf::Font m_font;
	sf::Text m_menu[2];
};