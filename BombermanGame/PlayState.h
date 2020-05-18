#pragma once
#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"
#include "Explosion.h"

#include <SFML/Graphics.hpp>

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
	sf::Time GetElapsedTime() const;
	bool IsPlayerOnTeleport();
	bool IsPlayerOnPowerUp();
	void ChangeBlocks();

private:
	Map m_map;
	Explosion *m_explosion;
	Player m_player;
	Bomb *m_bomb;
	GameClock m_clock;
};