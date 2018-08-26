#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "Faction.h"

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

/*
* FactionTable: Root table of the faction databases.
* Maps all faction names to their corresponding data tables.
*/
class FactionTable
{
private:
	std::unordered_map<std::string, Faction> Factions;

public:
	FactionTable();
	~FactionTable();
	
	//Populate with data
	void AddFaction(std::string);
	int GetFactionCount() { return Factions.size(); }

	//Get references to data
	Faction& GetFaction(std::string);
	Weapon& GetWeapon(std::string, std::string = "");
	Model& GetModel(std::string, std::string = "");

	void ListAll(bool = true);
	void PrintFaction(std::string);
	void PrintFaction(size_t);
};
