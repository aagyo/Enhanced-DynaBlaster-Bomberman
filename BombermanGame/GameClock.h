#pragma once
#include "Chronometer.h"

class GameClock
{
public:
	GameClock();
	~GameClock() = default;

public:
	void Pause();
	void Resume();
	void Reset();
	bool IsRunning() const;
	sf::Time GetElapsedTime() const;

private:
	sftools::Chronometer m_clock;
};