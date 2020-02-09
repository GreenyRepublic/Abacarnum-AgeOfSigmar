#pragma once

#include <set>
// Data containers for bundles of data that are generally owned and tied to behaviours, but also need to be thrown around into other processes
// E.g. a weapon has a profile and behaviours (attack, etc), but we may need to reference the profile information elsewhere when resolving special abilities

struct ModelProfile
{
	std::string name { "" };
	size_t move{ 0 };
	size_t save{ 0 };
	size_t bravery{ 0 };
	size_t wounds{ 0 };
	size_t currentWounds{ 0 };
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
};

struct UnitProfile
{
	ModelProfile typeModel{ ModelProfile() };
	size_t maxModelCount{ 0 };
	std::set<size_t> currentModels{};

	UnitProfile() {};
	UnitProfile(const ModelProfile& typemodel, const size_t modelcount) :
		typeModel(typemodel),
		maxModelCount(modelcount),
		currentModels(modelcount, typeModel.wounds)
	{};
};

struct BattleshockProfile
{
	size_t losses;
	BattleshockProfile(size_t losses) : 
		losses(losses) {};
};

struct AttackProfile
{
	WeaponProfile attackingWeapon{ WeaponProfile() };
	ModelProfile attackingModel{ ModelProfile() };
	ModelProfile defendingModel{ ModelProfile() };

	size_t hits{ 0 };
	size_t wounds{ 0 };
	size_t mortalWounds{ 0 };

	AttackProfile() {};
	AttackProfile(WeaponProfile& weapon, ModelProfile& attackmodel, ModelProfile& defmodel, size_t hits, size_t wounds, size_t mortalwounds) :
		attackingWeapon(weapon),
		attackingModel(attackmodel),
		defendingModel(defmodel) {};
};

struct UnitAttack
{
	UnitProfile UnitProfile;
	std::vector<AttackProfile> AttackProfiles;
};
