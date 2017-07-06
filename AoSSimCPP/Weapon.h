#pragma once
#include <string>
#include <vector>
#include "Model.h"

//Header for Weapon.cpp
class Weapon
{
private:

	std::string Name;

	//Stats
	uint8_t Range;
	uint8_t Attacks;
	uint8_t ToHit;
	uint8_t ToWound;
	uint8_t Rend;
	uint8_t Damage;

public:
	Weapon(std::string name, uint8_t range, uint8_t attacks, uint8_t hitroll, uint8_t woundroll, uint8_t rend, uint8_t damage);
	~Weapon();

	bool HitRoll();
	bool WoundRoll();

	uint8_t GenerateWounds(Model*);

	std::string getName() { return Name; }
};

