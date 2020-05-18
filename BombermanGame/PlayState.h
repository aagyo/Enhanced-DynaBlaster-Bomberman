#pragma once
#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"

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

public:
	sf::Time GetElapsedTime() const;

private:
	Map m_map;
	Player m_player;
	Bomb m_bomb;
	GameClock m_clock;
	float m_deltaTime;
};