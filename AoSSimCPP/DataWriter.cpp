#include "stdafx.h"
#include "DataWriter.h"
#include "Weapon.h"
#include "Model.h"
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

void DataWriter::PrintData(const Weapon& weapon)
{
	std::cout << "	 |o| " << weapon.mEntityName << " "
		<< " |- " << "Range: " << (int)weapon.weaponProfile.range << '"'
		<< " | Attacks: " << (int)weapon.weaponProfile.attacks
		<< " | To Hit: " << (int)weapon.weaponProfile.tohit << "+"
		<< " | To Wound: " << (int)weapon.weaponProfile.towound << "+"
		<< " | Rend: " << -((int)weapon.weaponProfile.rend)
		<< " | Damage: " << (int)weapon.weaponProfile.damage
		<< std::endl;
}

void DataWriter::PrintData(const ModelProfile& model)
{
	std::cout << std::endl;
	std::cout << "|<>| " << DataWriter::ToUpper(model.mEntityName) << " |<>|" << std::endl;
	std::cout << std::endl;
	std::cout << "	|==| STATS |==|" << std::endl;
	std::cout << "	 |o| Move: " << (int)model.mModelProfile.move << '"' << std::endl;
	std::cout << "	 |o| Wounds: " << (int)model.mModelProfile.wounds << std::endl;
	std::cout << "	 |o| Bravery: " << (int)model.mModelProfile.bravery << std::endl;
	std::cout << "	 |o| Save: " << (int)model.mModelProfile.save << "+" << std::endl;

	std::cout << std::endl;
	std::cout << "	|==| MELEE WEAPONS |==|" << std::endl;
	for (auto& w : model.mMeleeWeapons) (PrintData(*w));

	std::cout << std::endl;
	std::cout << "	|==| RANGED WEAPONS |==|" << std::endl;
	for (auto& w : model.mRangedWeapos) PrintData(*w);

	std::cout << std::endl;
	std::cout << "	|==| METADATA |==|" << std::endl;
	std::cout << "	 |o| Unit Size: " << (int)model.mMatchedUnitSize << std::endl;
	std::cout << "	 |o| Points Cost: " << (int)model.mMatchedUnitCost << std::endl;
	std::cout << "	 |o| Keywords: ";
	for (auto& keyword : model.keywords)
	{
		std::cout << keyword << ", ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void DataWriter::PrintData(const Unit& unit)
{
	DataWriter::PrintHeader("Unit: " + unit.mEntityName, HeaderType::LevelOneHeader);
	DataWriter::PrintHeader("Type Model", HeaderType::LevelTwoHeader);
	PrintData(*unit.TypeModel);
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