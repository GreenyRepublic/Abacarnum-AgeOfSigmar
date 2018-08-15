#pragma once
#include "Model.h"

/* Unit: As defined by a Warscroll
 * A unit consists of one or more models (as defined by the warscroll). 
 * A unit attacks as a unit, takes casualties as a unit, and takes battleshock tests as a unit
 * Within the scope of this program no other data (position, etc) is needed
 */
class Unit : public GameEntity
{
private:
	uint8_t pointValue,
		modelsPerBatch,
		maxBatches, 
		Losses;
	std::vector<Model> Models;

	std::string Name;
	std::vector<std::string> Keywords;

	//For later
	//std::vector<Ability> Abilities;


public:
	Unit(Model&, int);
	~Unit();

	void MeleeAttack(Unit& target, int frontage);
	void TakeWounds(int count);
	void Battleshock();

	void EndTurn();
	void PrintStats();

	int GetLive() { return Models.size(); }
	int GetLosses() { return Losses; }	
};

