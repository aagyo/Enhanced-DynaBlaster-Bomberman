#pragma once
#include "State.h"

#include <stack>
#include <SFML/Graphics.hpp>

class StateMachine
{
public:
	StateMachine();
	~StateMachine() = default;

public:
	void Run(std::unique_ptr<State> state);
	void NextState();
	void LastState();
	void Update();
	void Draw();
	bool Running() const;
	void Quit();

public:
	template <typename T>
	static std::unique_ptr<T> Build(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

private:
	std::stack<std::unique_ptr<State>> m_states;
	bool m_resumeState;
	bool m_runningState;
};

template <typename T>
std::unique_ptr<T> StateMachine::Build(StateMachine& machine, sf::RenderWindow& window, bool replace)
{
	return std::unique_ptr<T>(new T(machine, window, replace));
}