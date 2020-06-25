#include "stdafx.h"
#include "FactionTable.h"
#include "NumberedMenu.h"
#include "types/ProfileTypes.h"


bool FactionTable::isInstantiated = false;

std::shared_ptr<FactionTable> FactionTable::GetFactionTable()
{
	static std::shared_ptr<FactionTable> instance;
	if (!isInstantiated)
	{
		auto ptr = new FactionTable();
		instance = (std::shared_ptr<FactionTable>(ptr));
		instance->InitialiseFactionTable();
		isInstantiated = true;
	}
	return instance;
}

FactionTable::FactionTable() : FactionEntries()
{
}

FactionTable::~FactionTable()
{
}

//Parse faction data from Lua files into their databases.
void FactionTable::InitialiseFactionTable()
{
	const std::string directory = "./factiondata";
	const std::filesystem::directory_iterator directoryIterator("factiondata");

	for ( auto& file : directoryIterator )
	{
		LoadFaction(file);
	}

	std::cout << "Successfully loaded " << GetFactionCount() << " factions. View the Encyclopaedia for more details." << std::endl;
}

bool FactionTable::LoadFaction( std::filesystem::directory_entry file )
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
	
	FactionData* faction = new FactionData( facName );
	for (auto&& modelEntry : luabridge::pairs(factionLuaTable["models"]))
	{
		//Core stats
		ModelProfile model = ModelProfile(
			modelEntry.second["name"].tostring(),
			modelEntry.second["stats"]["move"],
			modelEntry.second["stats"]["save"],
			modelEntry.second["stats"]["bravery"],
			modelEntry.second["stats"]["wounds"]);
		
		//Melee weapons
		if (!modelEntry.second["meleeWeapons"].isNil())
		{ 
			for (auto&& weaponEntry : luabridge::pairs(modelEntry.second["meleeWeapons"]))
			{
				WeaponProfile weapon = WeaponProfile(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"]);
				
				model.meleeWeapons.insert(weapon);
			}
		}

		//Ranged weapons
		if (!modelEntry.second["rangedWeapons"].isNil())
		{
			for (auto&& weaponEntry : luabridge::pairs(modelEntry.second["rangedWeapons"]))
			{
				WeaponProfile weapon = WeaponProfile(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"]); 

				model.rangedWeapons.insert(weapon);
			}
		}

		//Keywords
		for (auto&& keyword : luabridge::pairs(modelEntry.second["keywords"]))
		{
			model.keywords.insert(keyword.second.tostring());
		}

		faction->AddModelProfile(model);
	}

	FactionEntries.insert(std::pair<std::string, FactionData*>(facName, faction));
	return true;
}

std::shared_ptr<FactionData> FactionTable::GetFaction( const std::string factionName) const
{
	return FactionEntries.at(factionName);
}

ModelProfile FactionTable::GetModelProfile(const std::string modelName, const std::string factionName) const
{
	if (!factionName.empty())
	{
		return (FactionEntries.at(factionName)->GetModelProfile(modelName));
	}

	else
	{
		for (auto& factionPair : FactionEntries)
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

ModelProfile FactionTable::GetModelUsingMenu()
{
	return ModelProfile();
}

void FactionTable::StartEncyclopedia()
{
	CREATE_NUMBERED_MENU(EncyclopediaMenu, void)

	for (auto& fac : FactionEntries)
	{
		EncyclopediaMenu.AddOption(MenuOption(fac.first, [=]() { this->PrintFactionData(this->currentEncycOption); }));
	}

	std::string input = "";
	size_t option = 0;
	while (1)
	{
		std::cout << "Enter a faction number or name for a full list of models, or enter '0' to return to the main menu." << std::endl;
		EncyclopediaMenu.PrintMenu();
		std::cin >> input;
		option = std::stoi(input);

		if (option == 0) break;
		currentEncycOption = option;
		EncyclopediaMenu.SelectOption(option);
	}
}

void FactionTable::PrintFactionData(size_t factionIndex) const
{
	auto iter = FactionEntries.begin();
	for (int i = 0; i < factionIndex - 1; ++i, ++iter);
	DataWriter::PrintData(*(iter->second));
}