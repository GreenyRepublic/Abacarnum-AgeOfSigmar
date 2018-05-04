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

//Parse model and weapon profiles into their databases. Returns false if parsing fails for whatever reason.
bool ParseData(FactionTable& table)
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
	else
	{
		std::cout << "Could not find /data/faction_list.xml! Aborting data parse." << std::endl;
		return false;
	}

	std::cout << "Successfully loaded " << table->GetCount() << " factions. View the Encyclopaedia for more details." << std::endl;
	return true;
}

void Stats(const std::string name, FactionTable *ft)
{
	Model* mod = ft->GetModel(name);
	if (mod != nullptr) mod->PrintStats();
}


//Crunches battle stats and poops out a file.
void Numberwang(std::vector<BattleStats>& stats)
{
	float AWins = 0;
	float ASurvivors = 0;
	float BSurvivors = 0;
	int battlenum = stats->size();

	for (auto i = stats->begin(); i != stats->end(); i++)
	{
		AWins += (*i).winner;
		if ((*i).winner) ASurvivors += (*i).survivors;
		else BSurvivors += (*i).survivors;
	}
	ASurvivors /= battlenum;
	BSurvivors /= battlenum;

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
	file << "Most Wins: " << Winner << "(" << WinNum << " | " << (100*WinNum/stats->size()) << "%)\n";
	file << "Avg. Survivors/Win (" << AName << "): " << ASurvivors << "\n";
	file << "Avg. Survivors/Win (" << BName << "): " << BSurvivors << "\n";
	
	file.close();
}

void SingleBattle(){}

	
void BatchBattle(FactionTable& factable)
{
	using namespace std;

	vector<BattleStats> battles;
	stringstream ss;
	string buffer;
	string ModelA;
	string ModelB;
	int numA;
	int numB;
	int frontage;
	int reps;


	cout << "Please enter a model for Unit A: " << endl;
	cin.ignore();
	getline(cin, ModelA, '\n');
	cout << "How many?" << endl;
	cin >> buffer;
	numA = stoi(buffer);
		
	std::cout << std::endl;

	cout << "Please enter a model for Unit B: " << endl;
	cin.ignore();
	getline(cin, ModelB, '\n');
	cout << "How many?" << endl;
	cin >> buffer;
	numB = stoi(buffer);

	std::cout << std::endl;

	//cout << "Please enter a battle width: " << endl;
	//cin >> buffer;
	//frontage = stoi(buffer);

	cout << "Fight how many battles?" << endl;
	cin >> buffer;
	reps = stoi(buffer);

	Model* A = factable->GetModel(ModelA);
	Model* B = factable->GetModel(ModelB);

	for (int i = 0; i < reps; i++)
	{
		Unit* SideA = new Unit(A, numA);
		Unit* SideB = new Unit(B, numB);
		battles.push_back(Battle(SideA, SideB, 10));
		delete(SideA);
		delete(SideB);
	}
	Numberwang(&battles);
	std::cout << std::endl;
}


std::vector<std::string> MenuStrings{
	"Fight Single Battle", 
	"Fight Batch Battles", 
	"Encyclopaedia", 
	"Exit"
};

enum MenuOption
{
	FightSingle = 1,
	FightBatch,
	Encyclopaedia,
	Exit
};

void PrintMainMenu()
{
	int j = 1;
	for (auto s : MenuStrings)
	{
		std::cout << j << ": " << s << std::endl;
		j++;
	}
}




int main()
{
	std::cout << ToUpper("Welcome to the Age of Sigmar Fight-O-Matic v") << version << std::endl;

	//Initialisation
	FactionTable *FacTable = new FactionTable();
	bool parse = ParseData(FacTable);
	if (!parse) return EXIT_FAILURE;
	std::wstring dir;

	CreateDirectoryA("records", NULL);

	//Begin menu loop.
	std::string input;
	std::stringstream ss;
	int opt;
	
	while (1)
	{
		input.clear();
		PrintMainMenu();

		std::cin >> input;
		opt = std::stoi(input);
		switch ((MenuOption)opt)
		{
		case(FightSingle):
			std::cout << "Sorry this ain't available yet." << std::endl;
			break;
		case(FightBatch):
			BatchBattle(FacTable);
			break;
		case(Encyclopaedia):
			FacTable->ListAll();
			break;
		case (Exit):
			break;
		default:
			std::cout << "Invalid Entry!" << std::endl;
			break;
		}
	}
    return EXIT_SUCCESS;
}