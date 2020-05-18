#pragma once
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"
#include "DestroyBlocks.h"
#include "Explosion.h"

class Window
{
public:
	Window();
	~Window() = default;

public:
	void ShowWindow();
	void CheckForCollision();
	sf::Time GetElapsedTime() const;
	GameClock m_clock;

private:
	static const uint16_t m_windowHeight = 816;
	static const uint16_t m_windowWidth = 816;

	Map m_map;
	Player m_player;
	Bomb m_bomb;
	Explosion *m_explosion;

	sf::RenderWindow m_window;
};