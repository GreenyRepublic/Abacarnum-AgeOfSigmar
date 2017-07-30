// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>

#include "Weapon.h"
#include "Model.h"
#include "Die.h"
#include "FactionTable.h"
#include "Unit.h"
#include "Battle.h"
#include <ctime>

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

#define version 0.4

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

void Stats(const std::string name, FactionTable *ft)
{
	Model* mod = ft->GetModel(name);
	if (mod != nullptr) mod->PrintStats();
}

Unit* SetSide(std::string input, FactionTable *fac)
{
	std::stringstream ss;
	ss << input;
	char temp[64];
	std::string mod;
	int num;
	while (ss.getline(temp, 64, ' '))
	{
		try
		{
			num = std::stoi(temp);
			break;
		}
		catch (std::exception _Xinvalid_argument)
		{
			mod += temp;
		}
	}
	
	return new Unit(fac->GetModel(mod), num);
}

//Crunches battle stats and shits out a file.
void Numberwang(std::vector<BattleStats>* stats, int battlenum)
{
	float AWins = 0;

	for (auto a = stats->begin(); a != stats->end(); a++)
	{
		AWins += (*a).winner;
	}
	AWins = (100 * AWins) / battlenum;
	float BWins = 100 - AWins;

	std::string AName = (*stats)[0].sideA;
	std::string BName = (*stats)[0].sideB;

	std::cout << AName << " won: " << AWins << "%" << std::endl;
	std::cout << BName << " won: " << BWins << "%" << std::endl;

	std::string Winner = (AWins > BWins) ? AName : BName;
	int WinNum = (AWins > BWins) ? AWins : BWins;

	//Write data to file.
	time_t temp = time(0);
	struct tm *Time = localtime(&temp);

	std::stringstream ss; 
	ss << "records/" << AName << "_vs_" << BName << "_" << (Time->tm_mday);
	if (Time->tm_mon < 10) ss << 0; 
	ss << (Time->tm_mon) << (Time->tm_year + 1900) << "_" << (Time->tm_sec) << (Time->tm_min);
	ss << (Time->tm_hour) << ".txt";

	std::string filename;
	ss >> filename;

	std::ofstream file;
	file.open(filename);

	file << AName << " versus " << BName << "\n";
	file << stats->size() << " Battles Run\n";
	file << "Most Wins: " << Winner << "(" << WinNum << " | " << (100*WinNum/stats->size()) << "%)";
	
	file.close();
}

enum MenuOption
{
	FightSingle,
	FightBatch,
	Encyclopaedia,
	Exit
};

std::vector<std::string> MenuStrings{"Fight Single Battle", "Fight Batch Battles", "Encyclopaedia", "Exit"};

void MainMenu()
{
	int j = 1;
	for (auto i = MenuStrings.begin(); i != MenuStrings.end(); i++)
	{
		std::cout << j << ": " << (*i) << std::endl;
		j++;
	}
}

int main()
{
	std::cout << ToUpper("Welcome to the Age of Sigmar Fight-O-Matic v") << version << std::endl;

	//Initialisation
	FactionTable *FacTable = new FactionTable();
	ParseData(FacTable);
	std::wstring dir;

	CreateDirectoryA("records", NULL);

	//Begin console loop
	std::string args[8];
	std::string input;
	std::stringstream ss;
	
	int battlenum = 100;
	std::vector<BattleStats> battles;
	while (1)
	{
		MainMenu();
		
		Unit* SideA = new Unit(FacTable->GetModel("Kroxigor", "Seraphon"), 3);
		Unit* SideB = new Unit(FacTable->GetModel("Liberators"), 10);
		
		for (int i = 1; i < battlenum + 1; i++)
		{
			Unit* SideA = new Unit(FacTable->GetModel("Kroxigor", "Seraphon"), 3);
			Unit* SideB = new Unit(FacTable->GetModel("Liberators"), 10);
			std::cout << "Battle: " << i << "/" << battlenum << std::endl;
			battles.push_back(Battle(SideA, SideB, 5));
		}

		Numberwang(&battles, battlenum);
		break;
	}

	char s;
	std::cin >> s;
    return 0;
}