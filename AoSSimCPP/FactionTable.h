#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "Faction.h"

#include <regex>
#include <filesystem>

/*
* FactionTable: Database of all factions and their data
* Contains tools for querying the database for model data and displaying data.
*/
class FactionTable
{
public:
	
	//Singleton implementation
	static FactionTable* GetInstance();

	//Populate with data
	void InitialiseFactionTableFromFiles( std::string directory = "./factiondata" );
	int GetFactionCount() { return Factions.size(); }

	//Get references to data
	Faction& GetFaction(std::string faction);
	std::weak_ptr<Model> GetModel(std::string model, std::string faction = "");

	void ListAllFactions( bool = true );
	void PrintFactionData( std::string factionname );
	void PrintFactionData( size_t factionid);

private:
	std::unordered_map<std::string, Faction*> Factions;
	bool LoadFaction(std::experimental::filesystem::directory_entry file);
	FactionTable();
	~FactionTable();

};
