#include "stdafx.h"
#include "FactionTable.h"

FactionTable::FactionTable()
{}

FactionTable::~FactionTable()
{
	for (auto& pair : Factions)
	{
		delete pair.second;
	}
}

//Parse faction data from Lua files into their databases.
void FactionTable::InitialiseTableFromFiles( std::string directory )
{
	std::experimental::filesystem::directory_iterator directoryIterator("factiondata");
	for ( auto& file : directoryIterator )
	{
		LoadFaction(file);
	}
	std::cout << "Successfully loaded " << GetFactionCount() << " factions. View the Encyclopaedia for more details." << std::endl;
}


bool FactionTable::LoadFaction( std::experimental::filesystem::directory_entry file )
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
	
	Faction* faction = new Faction( facName );
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

	Factions.insert(std::pair<std::string, Faction*>(facName, faction));
	return true;
}

Faction& FactionTable::GetFaction(std::string name)
{
	return *Factions.at(name);
}

std::shared_ptr<Model> FactionTable::GetModel(std::string name, std::string faction)
{
	if (!faction.empty())
	{
		return (GetFaction(faction).GetModel(name));
	}

	else
	{
		for (auto f : Factions)
		{
			try { 
				Faction& fac = *f.second;
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

void FactionTable::ListAll(const bool numbered)
{
	int label = 1;
	std::regex expr("([a-z]+)|([A-Z][a-z]+)");;
	
	for (auto fac : Factions)
	{
		std::string facname = fac.first;
		std::cout << label << ": " << facname << std::endl;
		label++;
	}
	std::cout << std::endl;
}

void FactionTable::PrintFaction(std::string facname)
{
	try 
	{ 
		GetFaction(facname).PrintStats();
	}
	catch (std::out_of_range o) 
	{ 
		std::cout << "Faction " << facname << " doesn't appear to exist, has a profile been made for it? (" << o.what() << ")" << std::endl; 
		return; 
	}
}

void FactionTable::PrintFaction(size_t index)
{
	auto iter = Factions.begin();
	for (int i = 0; i < index-1; i++) iter++;
	PrintFaction(iter->first);
}