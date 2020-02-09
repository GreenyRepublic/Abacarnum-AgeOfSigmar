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
	~FactionTable();

	static std::shared_ptr<FactionTable> GetFactionTable();
	void InitialiseFactionTable();

	std::shared_ptr<FactionData> GetFaction(const std::string faction) const;
	std::shared_ptr<Model> GetModel(const std::string model, const std::string faction = "") const;
	std::shared_ptr<Model> GetModelUsingMenu();
	size_t GetFactionCount() const { return FactionEntries.size(); }

	void StartEncyclopedia();
	void PrintFactionData( size_t factionindex) const;


private:
	FactionTable();
	bool LoadFaction(std::filesystem::directory_entry);

	static bool isInstantiated;
	std::unordered_map<std::string, std::shared_ptr<FactionData>> FactionEntries;

	int currentEncycOption;
};
