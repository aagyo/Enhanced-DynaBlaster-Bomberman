#pragma once
#include "State.h"
#include "StateMachine.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class LevelState : public State
{
public:
	LevelState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

public:
	void Pause() override;
	void Resume() override;
	void Update() override;
	void Draw() override;

public:
	static uint16_t m_currentLevel;
	void DeleteMusicBuffer();

private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bg;
	sf::Text m_text;
	sf::Font m_font;
	sf::SoundBuffer* m_soundBuffer;
	sf::Sound* m_sound;

private:
	std::vector<std::string> m_levels;
};