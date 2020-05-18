#pragma once

enum class PowerType {

	GoldFire = 0,			// max bomb radius
	GoldBomb,			// max bombs number		
	GoldSkate,			// max player speed
	Fire,			// +1 to the bomb radius
	BombUp,				// +1 player bombs
	Skate,				// ++ player speed
	LifeUp,				// +1 player life
	Clock,				// + aditional time to finish the level
	RemoteControl,		// destroy bomb when a button is pressed
	LineBomb,			// all bomb in line
	BlockPasser,		// allow player to walk on stones block
	Count
};