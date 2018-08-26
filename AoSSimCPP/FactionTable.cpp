#include "stdafx.h"
#include "FactionTable.h"
#include <regex>


FactionTable::FactionTable()
{}

FactionTable::~FactionTable()
{}

void FactionTable::AddFaction(std::string facname)
{
	Faction* faction = new Faction(facname);

	std::string fileName;
	pugi::xml_document facFile;

	//Models need weapons, so we parse weapons first
	fileName += "data/" + facname + "_weapons.xml";
	pugi::xml_parse_result result = facFile.load_file(fileName.c_str());
	if (result)
	{
		for (pugi::xml_node node = facFile.child("faction").child("weapon"); node; node = node.next_sibling("weapon"))
		{
			std::string name = node.attribute("name").value();
			size_t range = std::stoi(node.child("range").child_value());
			size_t attacks = std::stoi(node.child("attacks").child_value());
			size_t tohit = std::stoi(node.child("tohit").child_value());
			size_t towound = std::stoi(node.child("towound").child_value());
			size_t rend = std::stoi(node.child("rend").child_value());
			size_t damage = std::stoi(node.child("damage").child_value());

			faction->AddWeapon(Weapon(name, range, attacks, tohit, towound, rend, damage));
		}
	}

	//Now load models.
	fileName = "data/" + facname + "_models.xml";
	//std::cout << fileName << std::endl;
	result = facFile.load_file(fileName.c_str());

	if (result)
	{
		for (pugi::xml_node node = facFile.child("faction").child("model"); node; node = node.next_sibling("model"))
		{
			size_t move;
			size_t save;
			size_t bravery;
			size_t wounds;

			std::string name = node.attribute("name").value();
			
			pugi::xml_node stats = node.child("stats");
			
			
			move = std::stoi(stats.child("move").child_value());
			save = std::stoi(stats.child("save").child_value());
			bravery = std::stoi(stats.child("bravery").child_value());
			wounds = std::stoi(stats.child("wounds").child_value());

			int size = std::stoi(node.child("size").child_value());
			int cost = std::stoi(node.child("cost").child_value());

			Model model(name, move, wounds, bravery, save, size, cost, facname);

			for (pugi::xml_node weapons = node.child("weapons").first_child(); weapons; weapons = weapons.next_sibling())
			{
				Weapon* weap = faction->GetWeapon(weapons.child_value());
				if (weap == nullptr)
				{
					continue;
				}
				//std::cout << weapons.child_value() << std::endl;
				//std::cout << weapons.attribute("type").value() << std::endl;
				model.AddWeapon(static_cast<std::string>(weapons.attribute("type").value()) == "melee", weap);
			}

			faction->AddModel(model);
			//std::cout << "Added model " << name << " to faction " << facname << "." << std::endl;
		}

		Factions.insert(std::pair<std::string, Faction*>(facname, faction));
	}
	//std::cout << "Successfully loaded " << Factions->size() << " factions" << std::endl;
}

Faction* FactionTable::GetFaction(std::string name)
{
	try
	{
		return Factions.at(name);
	}
	catch (std::out_of_range o) 
	{ 
		std::cout << "Cannot find faction " << name << "! (" << o.what() << ")" << std::endl; 
	}
}

Weapon* FactionTable::GetWeapon(std::string name, std::string faction)
{
	if (!faction.empty())
	{
		try
		{
			Faction* fac = GetFaction(faction);
			return (fac->GetWeapon(name));
		}
		catch (std::out_of_range o)
		{
			std::cout << "Cannot find weapon " << name << "! (" << o.what() << ")" << std::endl;
			return nullptr;
		}
	}
}

Model* FactionTable::GetModel(std::string name, std::string faction)
{
	if (!faction.empty())
	{
		try
		{
			Faction* fac = GetFaction(faction);
			return (fac->GetModel(name));
		}
		catch (std::out_of_range o) 
		{ 
			std::cout << "Cannot find model " << name << "! (" << o.what() << ")" << std::endl;
			return nullptr;
		}
	}

	else
	{
		for (auto f : Factions)
		{
			Faction* fac = f.second;
			if (fac->GetModel(name) != nullptr) return fac->GetModel(name);
		}		
		std::cout << "Cannot find model " << name << "!" << std::endl;
		return nullptr;
	}
}

void FactionTable::ListAll(const bool numbered)
{
	int i = 1;
	std::regex expr("([a-z]+)|([A-Z][a-z]+)");;
	
	for (auto fac : Factions)
	{
		std::string facname = fac.first;
		std::cout << i << ": " << facname << std::endl;
		i++;
	}
	std::cout << std::endl;
}

void FactionTable::ListFaction(std::string facname)
{
	Faction* fac;
	try { fac = GetFaction(facname); }
	catch (std::out_of_range o) { std::cout << "Faction " << facname << " doesn't appear to exist, has a profile been made for it? (" << o.what() << ")" << std::endl; return; }
	fac->PrintStats();
}

void FactionTable::ListFaction(unsigned int index)
{
	auto iter = Factions.begin();
	for (int i = 0; i < index-1; i++) iter++;
	ListFaction(iter->first);
}