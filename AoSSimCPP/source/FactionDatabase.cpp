#include "stdafx.h"
#include "FactionDatabase.h"
#include "NumberedMenu.h"
#include "types/ProfileTypes.h"


bool FactionDatabase::sIsInstantiated = false;

std::shared_ptr<FactionDatabase> FactionDatabase::GetFactionDatabase()
{
	static std::shared_ptr<FactionDatabase> instance;
	if (!sIsInstantiated)
	{
		auto ptr = new FactionDatabase();
		instance = (std::shared_ptr<FactionDatabase>(ptr));
		instance->InitialiseFactionDatabase();
		sIsInstantiated = true;
	}
	return instance;
}

FactionDatabase::FactionDatabase() : mFactionEntries()
{
}

FactionDatabase::~FactionDatabase()
{
}

//Parse faction data from Lua files into their databases.
void FactionDatabase::InitialiseFactionDatabase()
{
	const std::filesystem::directory_iterator directoryIterator(scFactionDataDirectory);

	for ( auto& file : directoryIterator )
	{
		if (!file.is_directory())
		{
			ParseFactionDataFromFile(file);
		}
	}

	std::cout << "Successfully loaded " << GetFactionCount() << " factions. View the Encyclopaedia for more details." << std::endl;
}

bool FactionDatabase::ParseFactionDataFromFile( std::filesystem::directory_entry file )
{
	lua_State* L = luaL_newstate();
	auto filepath = file.path().string();
	int loadResult = luaL_dofile(L, filepath.c_str() );

	if (loadResult != 0)
		return false;

	luaL_openlibs(L);
	int callResult = lua_pcall(L, 0, 0, 0);
	
	luabridge::LuaRef factionLuaTable = luabridge::getGlobal(L, "faction");
	std::string facName = factionLuaTable["name"].tostring();
	
	std::shared_ptr<FactionData> faction = std::make_shared<FactionData>( facName );

	for (auto&& tablemodel : luabridge::pairs(factionLuaTable["models"]))
	{
		auto modelEntry = tablemodel.second;
		std::set<std::string> modelKeywords;
		for (int i = 0; i < modelEntry["keywords"].length(); ++i)
		{
			modelKeywords.insert(modelEntry["keywords"][i].tostring());
		}

		std::string modelName = modelEntry["name"].tostring();
		size_t modelMove = modelEntry["stats"]["move"];
		size_t modelSave = modelEntry["stats"]["save"];
		size_t modelBravery = modelEntry["stats"]["bravery"];
		size_t modelWounds = modelEntry["stats"]["wounds"];
		size_t modelBlockSize = modelEntry["matchedData"]["blockSize"];
		size_t modelBlockCost = modelEntry["matchedData"]["blockCost"];
		size_t modelMaxBlocks = modelEntry["matchedData"]["maxBlocks"];

		//Core stats
		ModelProfile model = ModelProfile(
			modelName,
			modelMove,
			modelSave,
			modelBravery,
			modelWounds,
			modelKeywords,
			modelBlockSize,
			modelBlockCost,
			modelMaxBlocks
			);
		
		//Melee weapons
		if (!tablemodel.second["meleeWeapons"].isNil())
		{ 
			for (auto&& weaponEntry : luabridge::pairs(tablemodel.second["meleeWeapons"]))
			{
				WeaponProfile weapon = WeaponProfile(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"]);
				
				model.mMeleeWeaponProfiles.insert(weapon);
			}
		}

		//Ranged weapons
		if (!tablemodel.second["rangedWeapons"].isNil())
		{
			for (auto&& weaponEntry : luabridge::pairs(tablemodel.second["rangedWeapons"]))
			{
				WeaponProfile weapon = WeaponProfile(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"]); 

				model.mRangedWeaponProfiles.insert(weapon);
			}
		}
		faction->AddModelProfile(model);
	}

	mFactionEntries[faction->GetName()] = faction;
	return true;
}

std::shared_ptr<FactionData> FactionDatabase::GetFactionData( const std::string factionName) const
{
	return mFactionEntries.at(factionName);
}

ModelProfile FactionDatabase::GetModelProfile(const std::string modelName, const std::string factionName) const
{
	if (!factionName.empty())
	{
		return (mFactionEntries.at(factionName)->GetModelProfile(modelName));
	}

	else
	{
		for (auto& factionPair : mFactionEntries)
		{
			try { 
				auto& faction = factionPair.second;
				return faction->GetModelProfile(modelName);
			}
			catch (std::out_of_range exception)
			{
				continue;
			}
		}
		throw std::out_of_range("Could not find model '" + modelName + "' in any faction.");
	}
}

void FactionDatabase::PrintFactionData(size_t factionIndex) const
{
	auto iter = mFactionEntries.begin();
	for (int i = 0; i < factionIndex - 1; ++i, ++iter);
	DataWriter::PrintData(*(iter->second));
}