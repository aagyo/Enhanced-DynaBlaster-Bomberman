#pragma once
#include <memory>

#include <SFML/Graphics.hpp>

class StateMachine;

class State
{
public:
	State(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
	State(State&& other) noexcept = default;
	State& operator=(State&& other) noexcept = default;
	virtual ~State() = default;

public:
	State() = delete;
	State(const State& other) = delete;
	State& operator=(const State& other) = delete;

public:
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	std::unique_ptr<State> Next();
	bool isReplacing();

protected:
	StateMachine& m_machine;
	sf::RenderWindow& m_window;
	bool m_replacing;
	std::unique_ptr<State> m_next;
};