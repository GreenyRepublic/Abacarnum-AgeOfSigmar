#pragma once

/* Modifiers: Container structure for modifiers to hit rolls, range, wound rolls, etc.
* Lots of modifiers can get thrown around in a game for various different things this packages them together nicely.
*/

enum ModType {
	Add = 0,
	Multiply,
	Divide
};

struct Modifiers
{
	uint8_t duration;

	//Unit Modifiers
	std::pair<int8_t, ModType> move,
		save,
		bravery,
		wounds;

	//Weapon Modifiers
	std::pair<int8_t, ModType> range,
		attacks,
		tohit,
		towound,
		rend,
		damage;
};
