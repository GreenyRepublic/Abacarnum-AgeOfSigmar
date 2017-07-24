#pragma once
#include <string>
#include <vector>

#include "GameEntity.h"

//Header for Weapon.cpp
class Weapon : public GameEntity
{
private:
	
	//Stats
	int Range;
	int Attacks;
	int ToHit;
	int ToWound;
	int8_t Rend;
	int Damage;

public:
	Weapon(std::string, int, int, int, int, int, int);
	~Weapon();

	void PrintStats();

	bool HitRoll();
	bool WoundRoll();

	int GenerateWounds(int);
};

