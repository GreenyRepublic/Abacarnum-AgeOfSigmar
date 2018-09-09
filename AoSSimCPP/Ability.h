#pragma once
#include "GameEntity.h"
class Ability
{
private:
	size_t duration, turnsLeft;
	virtual bool Evaluate() = 0;
public:
	Ability();
	virtual ~Ability();
};

