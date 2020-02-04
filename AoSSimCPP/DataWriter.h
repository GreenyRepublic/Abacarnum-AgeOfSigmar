#pragma once
#include "stdafx.h"

template<class T>
class NumberedMenu;

class FactionData;
class Weapon;
class Model;
class Unit;
struct BattleStats;
struct BatchBattleData;


enum HeaderType
{
	BoxHeader = 1,
	LevelOneHeader,
	LevelTwoHeader,
};

//Stateless utility class for visualising the various wads of data that get chucked about, writing to files, etc.	
class DataWriter
{
public:
	static void PrintAppTitle(float version);

	static void PrintData(const FactionData& faction);
	static void PrintData(const Weapon& weapon);
	static void PrintData(const Model& model);
	static void PrintData(const Unit& unit);
	static void PrintData(const BattleStats& stats);
	static void PrintData(const BatchBattleData& batchdata);

	static void WriteBatchBattleDataToFile();

private:
	static std::string ToUpper(std::string);
	static void PrintHeader(std::string, HeaderType);
};