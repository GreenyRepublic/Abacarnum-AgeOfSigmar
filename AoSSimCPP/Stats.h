#pragma once
#include "stdafx.h"
#include "GameEntity.h"

/* Stats: Container structure for weapon and unit stats, and means to manipulate them
* Lots of modifiers can get thrown around in a game for various different things, this packages them together nicely.
* "Does unit I'm attacking have less than X save? Etc."
*/
//using modifier = std::pair<int8_t, ModType>;

enum ModType {
	Sum = 0,
	Multiply,
	Divide
};

//for Modifiers, these contain near-identical data to stats, with the caveat that they may only last some amount of time, and also contain an operator.
//E.g. 'Unit X casts debuff on Unit Y that halves it's health and subtracts 1 from rend'. This can get confusing quickly with passing raw numbers.
struct Modifier : GameEntity
{
	int duration = 0;
	ModType type;
	void PrintStats();
	void EndTurn();
};

struct WeaponStats
{
	//Weapon Stats
	size_t range,
		attacks,
		tohit,
		towound,
		rend,
		damage;
	WeaponStats();
	WeaponStats(size_t r, size_t a, size_t h, size_t w, size_t n, size_t d) :
		range(r), attacks(a), tohit(h), towound(w), rend(n), damage(d) {};
};

struct ModelStats
{
	//Unit Stats
	size_t move,
		save,
		bravery,
		wounds,
		currentWounds;
	ModelStats();
	ModelStats(size_t m, size_t s, size_t b, size_t w) :
		move(m), save(s), bravery(b), wounds(w), currentWounds(w){};
};


struct WeaponModifier : Modifier, WeaponStats
{
	WeaponStats operator+(const WeaponStats&); //Convolve a modifier with a base stat set
};

struct UnitModifier : Modifier, ModelStats
{
	ModelStats operator+(const ModelStats&); //Convolve a modifier with a base stat set
};
