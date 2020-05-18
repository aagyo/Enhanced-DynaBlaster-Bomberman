#include "pch.h"
#include "CppUnitTest.h"
#include "..\TestingDLL\TestingDLL.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UltimateTest
{
	TEST_CLASS(UltimateTest)
	{
	public:
		
		TEST_METHOD(Constructor)
		{
			CTestingDLL::Player newPlayer; //initializing newPlayer, number of lives should be 3 and radius should be 2

			Assert::IsTrue(newPlayer.GetRadiusStatus() == 2);
			Assert::IsTrue(newPlayer.GetNumberOfLives() == 3);
			Assert::IsTrue(newPlayer.GetMaxNoBombs() == 4);
		}

		TEST_METHOD(CopyConstructor)
		{
			CTestingDLL::Player newPlayer;
			CTestingDLL::Player copyPlayer(newPlayer); // creating new player which should have the same attributes as copied player

			Assert::IsTrue(copyPlayer.GetNumberOfLives() == newPlayer.GetNumberOfLives());
			Assert::IsTrue(copyPlayer.GetPositionX() == newPlayer.GetPositionX());
			Assert::IsTrue(copyPlayer.GetRadiusStatus() == newPlayer.GetRadiusStatus());
		}
		TEST_METHOD(GetNumberOfLives)
		{
			CTestingDLL::Player newPlayer; //new player initialization, expected number of lives 3
			Assert::IsTrue(newPlayer.GetNumberOfLives() == 3);

			newPlayer.SetLife(5); // new player expected number of lives is 3 + 5 = 8

			Assert::IsTrue(newPlayer.GetNumberOfLives() == 8);

			newPlayer.SetLife(-3); // new player expected number of lives is 8 - 3 = 5

			Assert::IsTrue(newPlayer.GetNumberOfLives() == 5);

		}
		TEST_METHOD(SetPositionX)
		{
			CTestingDLL::Player newPlayer; //new player initialization, expected position is 48

			Assert::IsTrue(newPlayer.GetPositionX() == 48);

			newPlayer.SetPositionX(10); // new players expected position should be 10

			Assert::IsTrue(newPlayer.GetPositionX() == 10);
		}
		TEST_METHOD(SetIsCollision)
		{
			CTestingDLL::Player newPlayer;

			newPlayer.SetIsCollision(false); // collision should now be dissabled

			Assert::IsTrue(newPlayer.GetIsCollision() == false);

			newPlayer.SetIsCollision(true); // collision should be back on

			Assert::IsTrue(newPlayer.GetIsCollision() == true);
		}
		TEST_METHOD(SetRadius)
		{
			CTestingDLL::Player newPlayer; // radius is 2 by default

			newPlayer.SetRadius(5); // radius should be added by 5 and be 7

			Assert::IsTrue(newPlayer.GetRadiusStatus() == 7);

			newPlayer.SetRadius(-2); //radius should be decreased by 2 and be 5 now

			Assert::IsTrue(newPlayer.GetRadiusStatus() == 5);
		}
		TEST_METHOD(SetPlayerSpeed)
		{
			CTestingDLL::Player newPlayer; // speed of player should be 1.2f

			newPlayer.SetPlayerSpeed(0.5f); // speed of player should be 1.7f now

			Assert::IsTrue(newPlayer.GetPlayerSpeed() == 1.7f);

			newPlayer.SetPlayerSpeed(-0.7f); // Speed of player should be 1.0f now

			Assert::IsTrue(newPlayer.GetPlayerSpeed() == 1.0f);
		}
		TEST_METHOD(SetIsDead)
		{
			CTestingDLL::Player newPlayer;

			newPlayer.SetIsDead(true); // new player should be dead now

			Assert::IsTrue(newPlayer.GetIsDead() == true);
		}
		TEST_METHOD(SetNumberOfBombs)
		{
			CTestingDLL::Player newPlayer;

			newPlayer.SetNumberOfBombs(5); // sets number of bombs to 5

			Assert::IsTrue(newPlayer.GetMaxNoBombs() == 5);
		}
		TEST_METHOD(SetHeight)
		{
			CTestingDLL::Player newPlayer; // initializing new player, expected Height is 48.0, expected Widht is 48.0

			Assert::IsTrue(newPlayer.GetPlayerHeight() == 48.0f);

			newPlayer.SetPlayerHeight(50.0f); // setting player height, expecte Height is 50.0

			Assert::IsTrue(newPlayer.GetPlayerHeight() == 50.0f);

			Assert::IsTrue(newPlayer.GetPlayerWidth() == 48.0f);

			newPlayer.SetPlayerWidth(50.0f); // setting player width, expecte Width is 50.0

			Assert::IsTrue(newPlayer.GetPlayerHeight() == 50.0f);
		}
	};
}
