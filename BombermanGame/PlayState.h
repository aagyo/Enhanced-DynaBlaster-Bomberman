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
	void CreateExplosions();
	void DrawExplosion(Bomb* thisBomb, uint16_t thisIndex);
	void InsertExplosion(Bomb *thisBomb);

private:
	Map m_map;
	std::vector<Explosion*> m_explosionsList;
	Player m_player;
	const uint16_t m_bombRadius = 2;
	GameClock m_clock;
	sf::Sound m_sound;
	sf::SoundBuffer m_soundBuffer;
};