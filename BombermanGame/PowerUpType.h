#pragma once

enum class PowerType {

	GoldFire = 0,			// max bomb radius
	GoldBomb,			// max bombs number		
	GoldSkate,			// max player speed
	Fire,			// +1 to the bomb radius
	BombUp,				// +1 player bombs
	Skate,				// ++ player speed
	Detonator,          // detonates all bombs
	LifeUp,				// +1 player life
	Clock,				// + aditional time to finish the level
	BlockPasser,		// allow player to walk on stones block
	Count
};