#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "FactionData.h"

#include <regex>
#include <filesystem>

/*
* FactionTable: Database of all factions and their data
* Contains tools for querying the database for model data and displaying data.
*/
class FactionTable
{
public:
	static FactionTable* GetInstance();

	//Populate with data
	void InitialiseFactionTableFromFiles( std::string directory = "./factiondata" );

	FactionData& FindFaction(std::string faction);
	std::shared_ptr<Model> FindModel(std::string model, std::string faction = "");
	
	//Select a model using a menu interface
	std::shared_ptr<Model> QueryModel();

	//Data browser/encyclopedia
	void Encyclopedia();

	size_t GetFactionCount() const { return Factions.size(); }
	void PrintFactionData( size_t factionindex);

private:
	std::unordered_map<std::string, FactionData*> Factions;
	bool LoadFaction(std::experimental::filesystem::directory_entry file);
	FactionTable();
	~FactionTable();

};
