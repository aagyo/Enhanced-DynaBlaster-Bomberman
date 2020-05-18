#pragma once
#include "State.h"
#include "StateMachine.h"
#include "Player.h"
#include "Map.h"
#include "GameClock.h"
#include "Bomb.h"
#include "Explosion.h"
#include "GameBar.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

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
	bool IsPlayerOnEnemy();	

public:
	sf::Time GetElapsedTime() const;

public:

	void WriteStatsInFile();
	void ReadStatsFromFile();
	void WriteLifeInFile();

private:
	void CreateExplosions();
	void VerifyEnemyDead(const Enemy* enemy);
	void InsertExplosion(Bomb* thisBomb);
	void DrawExplosion(Bomb* thisBomb, uint16_t thisIndex);

private:
	void DeleteMusicBuffer();

private:
	Map m_map;
	Player m_player;
	GameClock m_clock;
	GameBar* m_bar;
	sf::Sound* m_sound;
	sf::SoundBuffer* m_soundBuffer;
	std::vector<Explosion*> m_explosionsList;
	bool m_wasPlayerOnFire = false;
};