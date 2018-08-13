#include "stdafx.h"
#include "Stats.h"


void Modifier::EndTurn() {
	duration--;
	if (duration == 0) delete(this);
}

WeaponStats WeaponModifier::operator+(const WeaponStats& rhs)
{
	return WeaponStats(rhs.range + this->range, 
		rhs.attacks + this->attacks, 
		rhs.tohit + this->tohit, 
		rhs.towound + this->towound, 
		rhs.rend + this->rend, 
		rhs.damage + this->damage);
}

ModelStats UnitModifier::operator+(const ModelStats& rhs)
{
	return ModelStats(rhs.move + this->move, 
		rhs.save + this->save, 
		rhs.bravery + this->bravery, 
		rhs.wounds + this->wounds);
}

WeaponStats::WeaponStats() : range(0), attacks(0), tohit(0), towound(0), rend(0), damage(0)
{
}

ModelStats::ModelStats() : move(0), save(0), bravery(0), wounds(0)
{
}
