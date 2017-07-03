// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Weapon.h"
#include "Model.h"
#include "Die.h"
#include "FactionTable.h"

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

//Takes a 'beautified' name (spaces and capitals) and standardises it for handling within the simulator.
//Allows for names to be written nice in the XML files whilst maintaining compatibility.
std::string Standardise(std::string in)
{
	int i = 0;
	std::string result;
	while (in[i] != NULL) { 
		const char c = (char)tolower(in[i]);
		if (in[i] != ' ') result += c;
		i++;
	}
	return result;
}

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
			table->AddFaction(Standardise(node.child_value()));
			std::cout << "Found " << node.attribute("allegiance").value() << " faction " << node.child_value() << std::endl;
		}
	}
	else std::cout << "Could not find /data/faction_list.xml! Aborting data parse." << std::endl;

	//std::cout << "TEST: " << table->GetCount() << std::endl;
}


int main()
{
	FactionTable *FacTable = new FactionTable();
	ParseData(FacTable);
    return 0;
}