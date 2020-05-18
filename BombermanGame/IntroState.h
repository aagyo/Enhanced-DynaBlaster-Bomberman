#pragma once
#include "State.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

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
	void DeleteMusicBuffer();

private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bg;
	sf::Sound* m_sound;
	sf::SoundBuffer* m_soundBuffer;
};