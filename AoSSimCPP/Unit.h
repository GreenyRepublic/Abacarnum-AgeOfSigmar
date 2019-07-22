#pragma once
#include "stdafx.h"
#include "Model.h"

/* Unit: As defined by a Warscroll
 * A unit consists of one or more models (as defined by the warscroll). 
 * A unit attacks as a unit, takes casualties as a unit, and takes battleshock tests as a unit
 * Within the scope of this program no other data (position, etc) is needed
 */


struct Battleshock
{
	size_t Losses;

	Battleshock(size_t l) : Losses(l) {};
};

class Unit : public GameEntity
{
private:
	size_t pointValue,
		maxBatches, 
		Losses;

	std::vector<Model> Models;
	std::shared_ptr<Model> typeModel;

	std::string Name;
	std::vector<std::string> Keywords;

	//For later
	//std::vector<Ability> Abilities;


public:
	Unit(const std::shared_ptr<Model>, size_t);
	~Unit();

	void MeleeAttack(Unit&, int);
	void RangedAttack(Unit&);
	void ResolveHits(std::vector<Attack>);
	void TakeBattleshock();

	void EndTurn();
	void PrintStats();

	int GetLive() { return Models.size(); }
	int GetLosses() { return Losses; }	
};

