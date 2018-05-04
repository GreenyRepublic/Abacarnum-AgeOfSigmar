#pragma once
#include <string>
#include <vector>

#include "GameEntity.h"
#include "Die.h"
#include "Model.h"
#include "Modifiers.h"

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

	//To be added
	//std::vector<Ability> Abilities;

	int MakeRoll(Modifiers, uint8_t);

public:
	Weapon(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	~Weapon();

	void PrintStats();
	void EndTurn();

	uint8_t GenerateWounds(uint8_t, Modifiers);
};

