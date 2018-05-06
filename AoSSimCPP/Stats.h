#pragma once
#include "stdafx.h"
#include "GameEntity.h"

/* Stats: Container structure for weapon and unit stats, and means to manipulate them
* Lots of modifiers can get thrown around in a game for various different things, this packages them together nicely.
* "Does unit I'm attacking have less than X save? Etc."
*/
//using modifier = std::pair<int8_t, ModType>;

enum ModType {
	Add = 0,
	Multiply,
	Divide
};

//for Modifiers, these contain near-identical data to stats, with the caveat that they may only last some amount of time, and also contain an operator.
//E.g. 'Unit X casts debuff on Unit Y that halves it's health and subtracts 1 from rend'. This can get confusing quickly with passing raw numbers.
struct Modifier : GameEntity
{
	int duration = 0;
	void PrintStats();
	void EndTurn();
};

struct WeaponModifier : Modifier, WeaponStats
{
	WeaponStats operator+(WeaponStats&); //Convolve a modifier with a base stat set
};

struct UnitModifier : Modifier, ModelStats
{
	ModelStats operator+(ModelStats&); //Convolve a modifier with a base stat set
};

struct WeaponStats
{
	//Weapon Stats
	int8_t range,
		attacks,
		tohit,
		towound,
		rend,
		damage;
};

struct ModelStats
{
	//Unit Stats
	int8_t move,
		save,
		bravery,
		wounds,
		currentWounds;
};