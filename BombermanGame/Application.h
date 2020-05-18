#pragma once
#include "StateMachine.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
	Application() = default;
	~Application() = default;
	Application(const Application& other) = default;
	Application(Application&& other) noexcept = default;
	Application& operator=(const Application& other) = default;
	Application& operator=(Application&& other) noexcept = default;
	
public:
	void Run();

private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
	const uint16_t m_windowSizeWidth = 816;
	const uint16_t m_windowSizeHeight = 864;
	const uint16_t m_framesPerSecond = 144;
};