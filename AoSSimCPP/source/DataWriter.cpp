#include "stdafx.h"
#include "DataWriter.h"


#include "Unit.h"
#include "Battle.h"

void DataWriter::PrintAppTitle(float version)
{
	std::stringstream ss;
	ss << version;

	std::string versionstring;
	ss >> versionstring;

	PrintHeader("Welcome to the Age of Sigmar BattleSim v" + versionstring, BoxHeader);
}

void DataWriter::PrintData(const FactionData& faction)
{

}

void DataWriter::PrintData(const WeaponProfile& weapon)
{
	std::cout << "	 |o| " << weapon.mWeaponName << " "
		<< " |- " << "Range: " << (int)weapon.mRange << '"'
		<< " | Attacks: " << (int)weapon.mAttacks
		<< " | To Hit: " << (int)weapon.mToHit << "+"
		<< " | To Wound: " << (int)weapon.mToWound << "+"
		<< " | Rend: " << -((int)weapon.mRend)
		<< " | Damage: " << (int)weapon.mDamage
		<< std::endl;
}

void DataWriter::PrintData(const ModelProfile& model)
{
	std::cout << std::endl;
	std::cout << "|<>| " << DataWriter::ToUpper(model.mName) << " |<>|" << std::endl;
	std::cout << std::endl;
	std::cout << "	|==| STATS |==|" << std::endl;
	std::cout << "	 |o| Move: " << (int)model.mMove << '"' << std::endl;
	std::cout << "	 |o| Wounds: " << (int)model.mWounds << std::endl;
	std::cout << "	 |o| Bravery: " << (int)model.mBravery << std::endl;
	std::cout << "	 |o| Save: " << (int)model.mSave << "+" << std::endl;

	std::cout << std::endl;
	std::cout << "	|==| MELEE WEAPONS |==|" << std::endl;
	for (auto& weapon : model.mMeleeWeaponProfiles) (PrintData(weapon));

	std::cout << std::endl;
	std::cout << "	|==| RANGED WEAPONS |==|" << std::endl;
	for (auto& weapon : model.mRangedWeaponProfiles) PrintData(weapon);

	std::cout << std::endl;
	std::cout << "	|==| METADATA |==|" << std::endl;
	std::cout << "	 |o| Keywords: ";

	for (auto& keyword : model.mKeywords)
	{
		std::cout << keyword << ", ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void DataWriter::PrintData(const BattleStats& stats)
{
}

void DataWriter::PrintData(const BatchBattleData& batchdata)
{

}

void DataWriter::PrintHeader(std::string title, HeaderType level)
{
	switch (level)
	{
	case BoxHeader:
		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;
		std::cout << "|| " << title << " ||" << std::endl;
		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;
		break;

	case LevelOneHeader:
		std::cout << "|<>| " << title << " |<>|" << std::endl;
		break;

	case LevelTwoHeader:
		std::cout << "|==| " << title << " |==|" << std::endl;
		break;

	default:
		break;
	}
}

std::string DataWriter::ToUpper(std::string in)
{
	if (in.empty()) return  "";
	else
	{
		return static_cast<char>(toupper(in.at(0))) + ToUpper(in.substr(1));
	}
}