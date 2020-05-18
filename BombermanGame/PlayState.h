#pragma once
#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"
#include "Explosion.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class PlayState : public State
{
public:
	PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

public:
	void Pause() override;
	void Resume() override;
	void Update() override;
	void Draw() override;

public:
	void CreateMap();
	void CheckForCollision();

public:
	bool IsPlayerOnTeleport();
	bool IsPlayerOnPowerUp();

public:
	sf::Time GetElapsedTime() const;

private:
	void DrawExplosion(Bomb* thisBomb);

private:
	Map m_map;
	Explosion *m_explosion;
	Player m_player;
	const uint16_t bombRadius = 2;
	GameClock m_clock;
	sf::Sound m_sound;
	sf::SoundBuffer m_soundBuffer;
};