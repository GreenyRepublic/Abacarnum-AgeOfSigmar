#include "stdafx.h"
#include "FactionTable.h"
//B#include "MenuOptions.h"


FactionTable* FactionTable::GetInstance()
{
	static FactionTable* instance = new FactionTable();
	return instance;
}

FactionTable::FactionTable()
{
	
}

FactionTable::~FactionTable()
{
	for (auto& pair : Factions)
	{
		delete pair.second; 
	}
}

//Parse faction data from Lua files into their databases.
void FactionTable::InitialiseFactionTableFromFiles( std::string directory )
{
	std::filesystem::directory_iterator directoryIterator("factiondata");
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
	{
		return false;
	}

	luaL_openlibs(L);
	int callResult = lua_pcall(L, 0, 0, 0);
	
	luabridge::LuaRef factionLuaTable = luabridge::getGlobal(L, "faction");
	std::string facName = factionLuaTable["name"].tostring();
	
	FactionData* faction = new FactionData( facName );
	for (auto&& modelEntry : luabridge::pairs(factionLuaTable["models"]))
	{
		//Core stats
		std::shared_ptr<Model> model = std::make_shared<Model>(
			modelEntry.second["name"].tostring(),
			modelEntry.second["stats"]["move"],
			modelEntry.second["stats"]["save"],
			modelEntry.second["stats"]["bravery"],
			modelEntry.second["stats"]["wounds"],
			modelEntry.second["matchedData"]["unitSize"],
			modelEntry.second["matchedData"]["unitCost"],
			facName);
		
		//Melee weapons
		if (!modelEntry.second["meleeWeapons"].isNil())
		{ 
			for (auto&& weaponEntry : luabridge::pairs(modelEntry.second["meleeWeapons"]))
			{
				std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"],
					WeaponType::Melee
					);
				model->AddWeapon(weapon);
			}
		}

		//Ranged weapons
		if (!modelEntry.second["rangedWeapons"].isNil())
		{
			for (auto&& weaponEntry : luabridge::pairs(modelEntry.second["rangedWeapons"]))
			{
				std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(
					weaponEntry.second["name"].tostring(),
					weaponEntry.second["range"],
					weaponEntry.second["attacks"],
					weaponEntry.second["toHit"],
					weaponEntry.second["toWound"],
					weaponEntry.second["rend"],
					weaponEntry.second["damage"],
					WeaponType::Ranged
					);
				model->AddWeapon(weapon);
			}
		}

		//Keywords
		for (auto&& keyword : luabridge::pairs(modelEntry.second["keywords"]))
		{
			model->AddKeyword(keyword.second.tostring());
		}

		faction->AddModel(model);
	}

	Factions.insert(std::pair<std::string, FactionData*>(facName, faction));
	return true;
}

FactionData& FactionTable::FindFaction(std::string name)
{
	return *Factions.at(name);
}

std::shared_ptr<Model> FactionTable::FindModel(std::string name, std::string faction)
{
	if (!faction.empty())
	{
		return (FindFaction(faction).GetModel(name));
	}

	else
	{
		for (auto f : Factions)
		{
			try { 
				FactionData& fac = *f.second;
				return fac.GetModel(name);
			}
			catch (std::out_of_range e)
			{
				continue;
			}
		}
		throw std::out_of_range("Could not find model in any faction.");
	}
}

std::shared_ptr<Model> FactionTable::QueryModel()
{
	return nullptr;
}

void FactionTable::Encyclopedia()
{
	/*CREATE_NUMBERED_MENU(EncyclopediaMenu, FactionTable, size_t)

	for (auto fac : Factions)
	{
		EncyclopediaMenu.AddOption(MenuOption(fac.first, PrintFactionData));
	}

	std::string input;
	size_t option;
	while (1)
	{
		std::cout << "Enter a faction number or name for a full list of models, or enter '0' to return to the main menu." << std::endl;
		EncyclopediaMenu.PrintMenu();
		std::cin >> input;
		option = std::stoi(input);

		if (option == 0) return;
		else (EncyclopediaMenu(option));
	}
	auto test = PrintFactionData;*/
}

void FactionTable::PrintFactionData(size_t index)
{
	auto iter = Factions.begin();
	for (int i = 0; i < index - 1; i++, iter++);
	DataWriter::PrintData(*(iter->second));
}