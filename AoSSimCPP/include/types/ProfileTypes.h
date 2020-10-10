#pragma once
#include <set>
#include "stdafx.h"
// Data containers for bundles of data that are generally owned and tied to behaviours, but also need to be thrown around into other processes
// E.g. a weapon has a profile and behaviours (attack, etc), but we may need to reference the profile information elsewhere when resolving special abilities

class ProfileID
{
public:
	ProfileID() : mProfileID(mProfileCount++) {};

	const size_t GetID() const
	{
		return mProfileID;
	}

private:
	static size_t mProfileCount;
	const size_t mProfileID;
};

struct WeaponProfile : public ProfileID
{	
	std::string mWeaponName{ "" };
	size_t mRange{ 0 };
	size_t mAttacks{ 0 };
	size_t mToHit{ 0 };
	size_t mToWound{ 0 };
	size_t mRend{ 0 };
	size_t mDamage{ 0 };

	WeaponProfile(std::string name, size_t range, size_t attacks, size_t hit, size_t wound, size_t rend, size_t damage) :
		ProfileID(),
		mWeaponName(name),
		mRange(range),
		mAttacks(attacks),
		mToHit(hit),
		mToWound(wound),
		mRend(rend),
		mDamage(damage)
	{	}
	
	bool operator<(const WeaponProfile& other) const
	{
		return mWeaponName.compare(other.mWeaponName) < 0;
	}

private:
	WeaponProfile() = delete;
};

struct ModelProfile : public ProfileID
{
	//Core Data
	std::string mName { "" };
	size_t mMove{ 0 };
	size_t mSave{ 0 };
	size_t mBravery{ 0 };
	size_t mWounds{ 0 };
	std::set<WeaponProfile> mMeleeWeaponProfiles{};
	std::set<WeaponProfile> mRangedWeaponProfiles{};
	std::set<std::string> mKeywords{ {} };

	//Matched Play Data
	size_t mBlockSize{ 0 };
	size_t mMaxBlocks{ 0 };
	size_t mCostPerBlock{ 0 };


	ModelProfile() {};

	ModelProfile(std::string name, 
						size_t move, 
						size_t save, 
						size_t bravery, 
						size_t wounds, 
						std::set<std::string> keywords, 
						size_t blocksize, 
						size_t maxblocks, 
						size_t costperblock) :
		ProfileID(),
		mName(name),
		mMove(move), 
		mSave(save), 
		mBravery(bravery), 
		mWounds(wounds),
		mKeywords(keywords),
		mBlockSize(blocksize),
		mMaxBlocks(maxblocks),
		mCostPerBlock(costperblock)
	{	};
};
