#pragma once
#include <set>
#include "stdafx.h"
// Data containers for bundles of data that are generally owned and tied to behaviours, but also need to be thrown around into other processes
// E.g. a weapon has a profile and behaviours (attack, etc), but we may need to reference the profile information elsewhere when resolving special abilities

struct WeaponProfile
{
	std::string name{ "" };
	size_t range{ 0 };
	size_t attacks{ 0 };
	size_t tohit{ 0 };
	size_t towound{ 0 };
	size_t rend{ 0 };
	size_t damage{ 0 };

	WeaponProfile() {};
	WeaponProfile(std::string name, size_t range, size_t attacks, size_t hit, size_t wound, size_t rend, size_t damage) :
		name(name),
		range(range),
		attacks(attacks),
		tohit(hit),
		towound(wound),
		rend(rend),
		damage(damage) {};

	bool operator<(const WeaponProfile& other) const
	{
		return name.compare(other.name) < 0;
	}
};

struct ModelProfile
{
	std::string name { "" };
	size_t move{ 0 };
	size_t save{ 0 };
	size_t bravery{ 0 };
	size_t wounds{ 0 };
	size_t currentWounds{ 0 };
	std::set<WeaponProfile> meleeWeapons{ {} };
	std::set<WeaponProfile> rangedWeapons{ {} };
	std::set<std::string> keywords{ {} };

	ModelProfile() {};
	ModelProfile(std::string name, size_t move, size_t save, size_t bravery, size_t wounds, std::set<std::string> keywords = {}) :
		name(name),
		move(move), 
		save(save), 
		bravery(bravery), 
		wounds(wounds), 
		currentWounds(wounds),
		keywords(keywords) {};
};

// Contains additional model data for matched play
struct MatchedPlayProfile
{
	size_t blockSize{ 0 };
	size_t maxBlocksPerUnit{ 0 };
	size_t blockCost{ 0 };

	MatchedPlayProfile() {};
	MatchedPlayProfile(size_t blocksize, size_t maxblocks, size_t blockcost) :
		blockSize(blocksize),
		maxBlocksPerUnit(maxblocks),
		blockCost(blockcost) {}
};

struct UnitProfile
{
	ModelProfile typeModel{ ModelProfile() };
	size_t startingModelCount{ 0 };
	std::vector<size_t> currentModels{};

	UnitProfile() {};
	UnitProfile(const ModelProfile& typemodel, const size_t modelcount) :
		typeModel(typemodel),
		startingModelCount(modelcount),
		currentModels(modelcount, typeModel.wounds)
	{};
};