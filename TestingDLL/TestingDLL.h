// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the TESTINGDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// TESTINGDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported
#include <iostream>
#ifdef TESTINGDLL_EXPORTS
#define TESTINGDLL_API __declspec(dllexport)
#else
#define TESTINGDLL_API __declspec(dllimport)
#endif

// This class is exported from the dll
class TESTINGDLL_API CTestingDLL {
public:
	CTestingDLL(void);
	// TODO: add your methods here.
public:
class Player
{
public:
	Player() :m_numberOfLives(3),
		m_maximumNoBombs(4),
		m_radiusStatus(2),
		m_isCollision(true),
		m_playerSpeed(1.2f),
		m_playerWidth(48),
		m_playerHeight(48)
		{
	}
	

	~Player() = default;
	Player(const Player& other) = default;
	Player(Player&& other) noexcept = default;
	Player& operator=(const Player& other) = default;
	Player& operator=(Player&& other) noexcept = default;

public:
	float GetPlayerWidth() const
	{
		return m_playerWidth;
	};
	float GetPlayerHeight() const
	{
		return m_playerHeight;
	};
	float GetPositionX() const
	{
		return m_positionX;
	};
	float GetPositionY() const
	{
		return m_positionY;
	};
	float GetPlayerSpeed() const
	{
		return m_playerSpeed;
	};
	bool GetCanPlaceBomb() const;

public:
	void SetMaxNoBombs(uint16_t newMaximum);
	void SetPositionX(float newPositionX)
	{
		m_positionX = newPositionX;
	};
	void SetPositionY(float newPositionY)
	{
		m_positionY = newPositionY;
	};
	void SetCanPlaceBomb(bool isPossible);

public:
	void MovePlayer(float deltaTime);

private:
	void SetDeadAnimation();
	void SetStartPosition();

public:
	void SetNumberOfBombs(uint8_t number)
	{
		m_maximumNoBombs = number;
	};
	void SetRadius(uint8_t number)
	{
		m_radiusStatus += number;
	};
public:
	void SetLife(uint8_t number)
	{
		m_numberOfLives += number;
	};
	void SetIsCollision(bool status)
	{
		m_isCollision = status;
	};
	void SetPlayerSpeed(float speedAdded)
	{
		m_playerSpeed += speedAdded;
	};
	void SetIsDead(bool status)
	{
		m_isDead = status;
	};

	uint8_t GetRadiusStatus()
	{
		return m_radiusStatus;
	};
	uint8_t GetNumberOfLives()
	{
		return m_numberOfLives;
	};
	bool GetIsCollision()
	{
		return m_isCollision;
	}
	uint16_t GetMaxNoBombs() const
	{
		return m_maximumNoBombs;
	};
	bool GetIsDead()
	{
		return m_isDead;
	};
	void SetPlayerHeight(float set)
	{
		m_playerHeight = set;
	};
	void SetPlayerWidth(float set)
	{
		m_playerWidth = set;
	};
	void DeadAnimation(float deltaTime);

private:
	const float m_startPositionCoord = 48.f;
	float m_playerHeight = 45.f;
	float m_playerWidth = 45.f;
	const float m_timeAnimationPlayer = 0.6f;
	float m_positionX = 48;
	float m_positionY = 48;

private:
	bool m_placeBomb = true;
	bool m_isDead = false;
	bool m_deadAnimation = false;

private:
	uint8_t m_radiusStatus;
	uint16_t m_maximumNoBombs;
	uint8_t m_numberOfLives;
	float m_playerSpeed;
	bool m_isCollision;
	const uint8_t m_maxStatusNumber = 9;
};

};

extern TESTINGDLL_API int nTestingDLL;

TESTINGDLL_API int fnTestingDLL(void);
