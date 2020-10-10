#include "stdafx.h"


#include "FactionData.h"

#include <regex>
#include <filesystem>

/*
* FactionTable: Database of all factions and their data
* Contains tools for querying the database for model data and displaying data.
*/
class FactionDatabase
{
public:
	~FactionDatabase();

	static std::shared_ptr<FactionDatabase> GetFactionDatabase();
	void InitialiseFactionDatabase();

	std::shared_ptr<FactionData> GetFactionData(const std::string faction) const;
	ModelProfile GetModelProfile(const std::string model, const std::string faction = "") const;

	//ModelProfile GetModelUsingMenu();
	size_t GetFactionCount() const { return mFactionEntries.size(); }
	void PrintFactionData( size_t factionindex) const;


private:
	FactionDatabase();
	bool ParseFactionDataFromFile(std::filesystem::directory_entry);

	static bool sIsInstantiated;
	std::unordered_map<std::string, std::shared_ptr<FactionData>> mFactionEntries;

	int mCurrentEncycOption;
	static constexpr char* scFactionDataDirectory = "./lua/factiondata";
};
