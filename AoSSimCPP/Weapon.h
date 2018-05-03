#pragma once
#include <string>
#include <vector>

#include "GameEntity.h"

/*
* Weapon: Encapsulates a weapon profile in AoS.
* Contains stats/data as well as methods for resolving hit and wound rolls.
*/

class Weapon : public GameEntity
{
private:
	
	//Stats
	uint8_t Range,
		Attacks,
		toHit,
		toWound,
		Rend,
		Damage;

public:
	Weapon(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	~Weapon();

	void PrintStats();
	bool HitRoll();
	bool WoundRoll();

	int GenerateWounds(int);
};

