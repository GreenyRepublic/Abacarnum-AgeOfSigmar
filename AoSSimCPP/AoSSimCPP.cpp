// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>

#include "Weapon.h"
#include "Model.h"
#include "Die.h"
#include "FactionTable.h"
#include "Unit.h"

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

#define version 0.1

//Parse model and weapon profiles into their databases
void ParseData(FactionTable *table)
{
	using namespace pugi;

	//First load factions file.
	xml_document factionDoc;
	xml_parse_result result = factionDoc.load_file("data/faction_list.xml");
	if (result)
	{
		for (xml_node node = factionDoc.child("factions").child("faction"); node; node = node.next_sibling("faction"))
		{
			//When a faction has been found parse out its individual data files.
			table->AddFaction(node.child_value());

			//std::cout << "Found " << node.attribute("allegiance").value() << " faction " << node.child_value() << std::endl;
			Faction* fac = table->GetFaction(node.child_value());
			//fac->PrintStats();
		}
	}
	else std::cout << "Could not find /data/faction_list.xml! Aborting data parse." << std::endl;

	std::cout << "Successfully loaded " << table->GetCount() << " factions. Type 'list' for more details." << std::endl;
}


void PrintHelp()
{
	std::cout << "Available commands:" << std::endl;

	std::cout << std::endl;

	std::cout << "help" << std::endl;

	std::cout << std::endl;

	std::cout << "list [name]" << std::endl;
	std::cout << "- Lists all loaded weapon and model profiles for an entered faction name. Lists all factions if no name is entered." << std::endl;
	std::cout << "  NOTE: Faction names must be entered all lower case with spaces removed. E.g. 'Stormcast Eternals' becomes 'stormcasteternals'" << std::endl;

	std::cout << std::endl;

	std::cout << "exit" << std::endl;
}

void List(const std::string name, FactionTable *ft)
{
	if (!name.empty())
	{
		ft->ListFaction(name);
	}
	else
	{
		ft->ListAll();
	}
}

int main()
{
	std::cout << "Welcome to the Age of Sigmar Fight-O-Matic v" << version << "!" << std::endl;

	//Initialisation
	FactionTable *FacTable = new FactionTable();
	ParseData(FacTable);

	
	//Begin console loop
	std::string args[8];
	std::string input;
	std::stringstream ss;

	Unit unitA();
	Unit unitB();

	while (1)
	{
		for (int i = 0; i < 8; i++) args[i] = "";
		ss.clear();

		std::cout << "> ";
		std::getline(std::cin, input);
		ss << input;

		for (int i = 0; i < 8; i++) { ss >> args[i]; }
		
		if (args[0] == "help") { PrintHelp(); }
		else if (args[0] == "list") { List(args[1], FacTable); }
		else if (input == "exit") { break; }

		else { std::cout << "Unrecognised Command! For a list type 'help'." << std::endl; }
	}

    return 0;
}