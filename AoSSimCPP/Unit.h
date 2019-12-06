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
public:
	Unit(const std::shared_ptr<Model> model, size_t size);
	~Unit();

	UnitAttacks MeleeAttack(Unit& target, int frontage = 10);
	UnitAttacks RangedAttack(Unit& target);

	void TakeAttacks(UnitAttacks attacks);
	void TakeBattleshock();

	void EndTurn();
	void PrintStats();

	size_t GetSurvivingModels() const { return Models.size(); }
	size_t GetLosses() const { return Losses; }	
	Model& GetTypeModel() const { return *TypeModel; }

private:

	friend class DataWriter;

	bool MakeSave(WeaponAttack attack);

	size_t PointValue;
	size_t MaxBatches;
	size_t Losses;

	std::vector<Model> Models;
	std::shared_ptr<Model> TypeModel;

	std::string Name;
	std::vector<std::string> Keywords;

	//For later
	//std::vector<Ability> Abilities;
};

