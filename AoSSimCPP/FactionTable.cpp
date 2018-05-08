#include "FactionTable.h"


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
	fileName += "data/" + facname + "_weapons.xml";
	pugi::xml_parse_result result = facFile.load_file(fileName.c_str());
	if (result)
	{
		for (pugi::xml_node node = facFile.child("faction").child("weapon"); node; node = node.next_sibling("weapon"))
		{
			std::string name = node.attribute("name").value();
			uint16_t range = std::stoi(node.child("range").child_value());
			uint16_t attacks = std::stoi(node.child("attacks").child_value());
			uint16_t tohit = std::stoi(node.child("tohit").child_value());
			uint16_t towound = std::stoi(node.child("towound").child_value());
			uint16_t rend = std::stoi(node.child("rend").child_value());
			uint16_t damage = std::stoi(node.child("damage").child_value());

			Weapon* weapon = new Weapon(name, range, attacks, tohit, towound, rend, damage);
			faction.AddWeapon(weapon);
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
			uint16_t move;
			uint16_t save;
			uint16_t bravery;
			uint16_t wounds;

			std::string name = node.attribute("name").value();
			
			pugi::xml_node stats = node.child("stats");
			
			
			move = std::stoi(stats.child("move").child_value());
			save = std::stoi(stats.child("save").child_value());
			bravery = std::stoi(stats.child("bravery").child_value());
			wounds = std::stoi(stats.child("wounds").child_value());

			int size = std::stoi(node.child("size").child_value());
			int cost = std::stoi(node.child("cost").child_value());

			Model* model = new Model(name, move, wounds, bravery, save, size, cost, facname);
			bool bad = 0;

			for (pugi::xml_node weapons = node.child("weapons").first_child(); weapons; weapons = weapons.next_sibling())
			{
				Weapon* weap = faction.GetWeapon(weapons.child_value());
				if (weap == nullptr)
				{
					bad = 1;
					break;
				}

				//std::cout << weapons.child_value() << std::endl;
				//std::cout << weapons.attribute("type").value() << std::endl;
				if ((std::string)weapons.attribute("type").value() == "melee") { model->AddWeapon(true, weap); }
				else { model->AddWeapon(false, weap); }
			}
			if (bad) continue;
			faction.AddModel(model);
			//std::cout << "Added model " << name << " to faction " << facname << "." << std::endl;
		}
		
		Factions.insert(std::pair<std::string, Faction>(facname, faction));
	}
	//std::cout << "Successfully loaded " << Factions->size() << " factions" << std::endl;
}

Faction* FactionTable::GetFaction(std::string name)
{
	try
	{
		return &Factions.at(name);
	}
	catch (std::out_of_range o) { std::cout << "Cannot find faction " << name << "! (" << o.what() << ")" << std::endl; }
}

Weapon* FactionTable::GetWeapon(std::string name, std::string faction = nullptr)
{
	if (!faction.empty())
	{
		try
		{
			Faction* fac = GetFaction(faction);
			return (fac->GetWeapon(name));
		}
		catch (std::out_of_range o) { std::cout << "Cannot find weapon " << name << "! (" << o.what() << ")" << std::endl; }
	}
}

Model * FactionTable::GetModel(std::string name, std::string faction)
{
	if (!faction.empty())
	{
		try
		{
			Faction* fac = GetFaction(faction);
			return (fac->GetModel(name));
		}
		catch (std::out_of_range o) { std::cout << "Cannot find model " << name << "! (" << o.what() << ")" << std::endl; }
		return nullptr;
	}

	else
	{
		for (auto f : Factions)
		{
			try 
			{
				Faction fac = f.second;
				return fac.GetModel(name);
			}
			catch (std::out_of_range o) { continue; }
		}		
		std::cout << "Cannot find model " << name << "! (" << ")" << std::endl;
		return nullptr;
	}
}
void FactionTable::ListAll()
{
	for (auto fac : Factions)
	{
		std::cout << fac.first << std::endl;
	}
}

void FactionTable::ListFaction(std::string facname)
{
	Faction* fac;
	try { fac = GetFaction(facname); }
	catch (std::out_of_range o) { std::cout << "Faction " << facname << " doesn't appear to exist, has a profile been made for it? (" << o.what() << ")" << std::endl; return; }
	fac->PrintStats();
}

