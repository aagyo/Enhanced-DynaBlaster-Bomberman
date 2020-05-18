#pragma once
#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"
#include "Explosion.h"
#include "GameBar.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	void StatusUpdate(const PowerType& powerUp);

private:
	bool IsPlayerOnTeleport();
	bool IsPlayerOnPowerUp();
	bool IsTimeZero();
	void IsPlayerOnFireBlock();
	

public:
	sf::Time GetElapsedTime() const;

private:
	void CreateExplosions();
	void DrawExplosion(Bomb* thisBomb, uint16_t thisIndex);
	void InsertExplosion(Bomb *thisBomb);

private:
	void DeleteMusicBuffer();

private:
	Map m_map;
	std::vector<Explosion*> m_explosionsList;
	Player m_player;
	GameClock m_clock;
	bool m_wasPlayerOnFire = false;
	GameBar* m_bar;
	sf::Sound* m_sound;
	sf::SoundBuffer* m_soundBuffer;

};