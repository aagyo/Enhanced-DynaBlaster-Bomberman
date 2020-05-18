#pragma once
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"

class Window
{
public:
	Window();
	~Window() = default;
	GameClock m_clock;

public:
	void ShowWindow();
	void CheckForCollision();
	sf::Time GetElapsedTime() const;

private:
	static const uint16_t m_windowHeight = 816;
	static const uint16_t m_windowWidth = 816;

	Map m_map;
	Player m_player;
	Bomb m_bomb;
	sf::RenderWindow m_window;
};

