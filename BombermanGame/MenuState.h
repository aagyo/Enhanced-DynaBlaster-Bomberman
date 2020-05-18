#pragma once
#include "State.h"
#include "StateMachine.h"

#include <SFML/Graphics.hpp>

class MenuState : public State
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

public:
	void Pause() override;
	void Resume() override;
	void Update() override;
	void Draw() override;

private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bg;
	sf::RectangleShape m_fader;
	sf::Color m_alpha;
};