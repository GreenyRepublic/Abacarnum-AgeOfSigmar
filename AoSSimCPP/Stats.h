#pragma once
#include "stdafx.h"
#include "GameEntity.h"

/* Stats: Container structure for weapon and unit stats, and means to manipulate them
* Lots of modifiers can get thrown around in a game for various different things, this packages them together nicely.
* "Does unit I'm attacking have less than X save? Etc."
*/
//using modifier = std::pair<int8_t, ModType>;


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

