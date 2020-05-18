#include "GameClock.h"

GameClock::GameClock()
{
	m_clock.reset();
}

sf::Time GameClock::GetElapsedTime() const
{
	return m_clock.getElapsedTime();
}

void GameClock::Pause()
{
	m_clock.pause();
}

void GameClock::Resume()
{
	m_clock.resume();
}

void GameClock::Reset()
{
	m_clock.reset();
}

bool GameClock::IsRunning() const
{
	return m_clock.isRunning();
}