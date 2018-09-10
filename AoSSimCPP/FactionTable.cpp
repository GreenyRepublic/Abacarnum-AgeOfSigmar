#include "stdafx.h"
#include "FactionTable.h"
#include <regex>


FactionTable::FactionTable()
{}

FactionTable::~FactionTable()
{}

void FactionTable::AddFaction(std::string facname)
{
	Faction faction(facname);

	std::string fileName;
	pugi::xml_document facFile;

	//Models need weapons, so we parse weapons first
	fileName += "./factiondata/" + facname + "_weapons.xml";
	pugi::xml_parse_result result = facFile.load_file(fileName.c_str());
	if (result)
	{
		for (pugi::xml_node node = facFile.child("faction").child("weapon"); node; node = node.next_sibling("weapon"))
		{
			std::string name = node.attribute("name").value();
			size_t range = std::stoi(node.child("range").child_value()),
				attacks = std::stoi(node.child("attacks").child_value()),
				tohit = std::stoi(node.child("tohit").child_value()),
				towound = std::stoi(node.child("towound").child_value()),
				rend = (-std::stoi(node.child("rend").child_value())),
				damage = std::stoi(node.child("damage").child_value());

			faction.AddWeapon(std::make_shared<Weapon>(name, range, attacks, tohit, towound, rend, damage));
		}
	}

	//Now load models.
	fileName = "./factiondata/" + facname + "_models.xml";
	//std::cout << fileName << std::endl;

	if (facFile.load_file(fileName.c_str()))
	{
		for (pugi::xml_node node = facFile.child("faction").child("model"); node; node = node.next_sibling("model"))
		{

			std::string name = node.attribute("name").value();
			pugi::xml_node stats = node.child("stats");
			
			size_t move = std::stoi(stats.child("move").child_value()),
				save = std::stoi(stats.child("save").child_value()),
				bravery = std::stoi(stats.child("bravery").child_value()),
				wounds = std::stoi(stats.child("wounds").child_value()),
				size = std::stoi(node.child("size").child_value()),
				cost = std::stoi(node.child("cost").child_value());

			auto model = std::make_shared<Model>(name, move, wounds, bravery, save, size, cost, facname);

			for (pugi::xml_node weapons = node.child("weapons").first_child(); weapons; weapons = weapons.next_sibling())
			{
				try {
					auto weap = faction.GetWeapon(weapons.child_value());
					model->AddWeapon(static_cast<std::string>(weapons.attribute("type").value()) == "melee", weap);
				}
				catch(std::out_of_range e)
				{
					continue;
				}
			}
			faction.AddModel(model);
			//std::cout << "Added model " << name << " to faction " << facname << "." << std::endl;
		}

		Factions.insert(std::pair<std::string, Faction>(facname, std::move(faction)));
	}
	//std::cout << "Successfully loaded " << Factions->size() << " factions" << std::endl;
}

Faction& FactionTable::GetFaction(std::string name)
{
	return Factions.at(name);
}

std::shared_ptr<Weapon> FactionTable::GetWeapon(std::string name, std::string faction)
{
	return (GetFaction(faction).GetWeapon(name));
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
				Faction& fac = f.second;
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