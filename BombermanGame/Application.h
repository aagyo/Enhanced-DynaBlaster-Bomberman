#pragma once
#include "IntroState.h"
#include "StateMachine.h"

#include <SFML/Graphics.hpp>

class Application
{
public:
	Application() = default;
	~Application() = default;

public:
	void Run();

private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
	const uint32_t m_windowSize = 816;
	const uint16_t m_framesPerSecond = 144;
};