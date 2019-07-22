#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "Faction.h"

#include <regex>
#include <filesystem>

/*
* FactionTable: Root table of the faction databases.
* Maps all faction names to their corresponding data tables.
*/
class FactionTable
{
private:
	std::unordered_map<std::string, Faction*> Factions;
	bool LoadFaction( std::experimental::filesystem::directory_entry file );

public:
	FactionTable();
	~FactionTable();
	
	//Populate with data
	void InitialiseTableFromFiles( std::string directory = "./factiondata" );
	int GetFactionCount() { return Factions.size(); }

	//Get references to data
	Faction& GetFaction(std::string faction);
	std::shared_ptr<Model> GetModel(std::string, std::string = "");

	void ListAll(bool = true);
	void PrintFaction(std::string);
	void PrintFaction(size_t);
};
