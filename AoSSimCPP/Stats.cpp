#include "stdafx.h"
#include "Stats.h"


void Modifier::EndTurn() {
	duration--;
	if (duration == 0) delete(this);
}

WeaponStats WeaponModifier::operator+(WeaponStats& stats)
{
	WeaponStats newStats;
	newStats.attacks = stats.attacks + this->attacks;
	newStats.damage = stats.damage + this->damage;
	newStats.range = stats.range + this->range;
	newStats.rend = stats.rend + this->rend;
	newStats.tohit = stats.tohit + this->tohit;
	newStats.towound = stats.towound + this->towound;

	return newStats;
}

ModelStats UnitModifier::operator+(ModelStats& stats)
{
	ModelStats newStats;
	newStats.wounds = stats.wounds + this->wounds;
	newStats.move = stats.move + this->move;
	newStats.bravery = stats.bravery + this->bravery;
	newStats.save = stats.save + this->save;

	return newStats;
}