#pragma once
#include <string>
#include <vector>

#include "GameEntity.h"

//Header for Weapon.cpp
class Weapon : public GameEntity
{
private:
	
	//Stats
	uint8_t Range;
	uint8_t Attacks;
	uint8_t ToHit;
	uint8_t ToWound;
	int8_t Rend;
	uint8_t Damage;

public:
	Weapon(std::string, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	~Weapon();

	bool HitRoll();
	bool WoundRoll();

	uint8_t GenerateWounds(uint8_t);
};

