// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Die.h"
#include "Weapon.h"
#include "Model.h"
#include "FactionTable.h"
#include "Unit.h"
#include "Battle.h"
#include "Printable.h"

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

static const float version = 0.55;

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
			table.AddFaction(node.child_value());

			//std::cout << "Found " << node.attribute("allegiance").value() << " faction " << node.child_value() << std::endl;
			//Faction* fac = table.GetFaction(node.child_value());
			//fac->PrintStats();
		}
	}
	else
	{
		std::cout << "Could not find /data/faction_list.xml! Aborting data parse." << std::endl;
		return false;
	}

	std::cout << "Successfully loaded " << table.GetFactionCount() << " factions. View the Encyclopaedia for more details." << std::endl;
	return true;
}


//Crunches battle stats and writes to file.
void WriteStats(std::vector<BattleStats>& stats, std::string& aname, std::string& bname)
{
	std::unordered_map<std::string, int> wins, survivors;
	size_t battlenum = stats.size();
	float turns = 0;

	for (auto stat : stats)
	{
		turns += stat.turns;
		wins[stat.Winner] += 1;
		survivors[stat.Winner] += stat.survivors;
	}

	turns /= battlenum;
	survivors[aname] /= battlenum;
	survivors[bname] /= battlenum;

	std::cout << aname << " won: " << ((100 * wins[aname])/battlenum) << "%" << std::endl;
	std::cout << bname << " won: " << ((100 * wins[bname])/battlenum) << "%" << std::endl;

	std::string Winner = (wins[aname] > wins[bname]) ? aname : bname;
	int WinNum = wins[Winner];

	//Write data to file.
	time_t temp = time(0);
	struct tm *Time = localtime(&temp);

	std::stringstream ss; 
	ss << "records/" << aname << " vs " << bname << " " << (Time->tm_mday);
	if (Time->tm_mon < 9) { ss << 0; }
	ss << (Time->tm_mon + 1) << (Time->tm_year + 1900) << "_" << (Time->tm_sec) << (Time->tm_min) << (Time->tm_hour) << ".csv";

	std::string filename;
	filename = ss.str();
	std::ofstream file(filename);

	file << "unit,winCount,winRate,avgSurvivorsPerWin,avgTurnsPerBattle\n";
	file << ",,,," << turns << "\n";
	file << aname << ',' << WinNum << ',' << (100 * WinNum / stats.size()) << '%,' << survivors[aname] << '\n';
	file << bname << ',' << battlenum - WinNum << ',' << (100.0 - (100 * WinNum / stats.size())) << '%,' << survivors[bname];
	
	file.close();
}

void SingleBattle(){}

void BatchBattle(FactionTable& factable)
{
	using namespace std;

	vector<BattleStats> battles;
	string buffer, ModelA, ModelB;
	std::shared_ptr<Model> A, B;
	int numA, numB, 
		frontage, 
		reps = 10;

	cout << "Please enter a model for Unit A: " << endl;
	cin.ignore();
	getline(cin, ModelA, '\n');
	while (true)
	{
		try
		{
			A = factable.GetModel(ModelA);
			break;
		}
		catch (std::out_of_range e)
		{
			std::cout << "Model " << ModelA << " not found, please try again." << std::endl;
			getline(cin, ModelA, '\n');
		}
	}

	cout << "How many?" << endl;
	cin >> buffer;
	numA = stoi(buffer);

	std::cout << std::endl;

	cout << "Please enter a model for Unit B: " << endl;
	cin.ignore();
	getline(cin, ModelB, '\n');

	while (true)
	{
		try
		{
			B = factable.GetModel(ModelB);
			break;
		}
		catch (std::out_of_range e)
		{
			std::cout << "Model " << ModelB << " not found, please try again." << std::endl;
			getline(cin, ModelB, '\n');
		}
	}
	
	cout << "How many?" << endl;
	cin >> buffer;
	numB = stoi(buffer);

	//cout << "Please enter a battle width: " << endl;
	//cin >> buffer;
	//frontage = stoi(buffer);

	cout << std::endl << "Fight how many battles?" << endl;
	cin >> buffer;
	reps = stoi(buffer);

	for (int i = 0; i < reps; i++)
	{
		auto a = Unit(A, numA);
		auto b = Unit(B, numB);
		battles.push_back(Battle(a, b, 10));
	}
	WriteStats(battles, A->GetName(), B->GetName());
	std::cout << std::endl;
}


std::vector<std::string> TopMenuStrings{
	"Fight Single Battle", 
	"Fight Batch Battles", 
	"Encyclopaedia", 
	"Exit"
};

enum TopMenuOptions
{
	FightSingle = 1,
	FightBatch,
	Encyclopaedia,
	Exit
};

void PrintMainMenu()
{
	int j = 1;
	for (auto s : TopMenuStrings)
	{
		std::cout << j << ": " << s << std::endl;
		j++;
	}
}

//Options for navigating encyclopedia entries
void Encyclopedia(FactionTable& table)
{
	std::string input;
	unsigned int opt;
	while (1)
	{
		table.ListAll(true);
		std::cout << "Enter a faction number or name for a full list of models, or enter '0' to return to the main menu." << std::endl;
		std::cin >> input;
		opt = std::stoi(input);

		if (opt == 0) return;
		else (table.PrintFaction(opt));
	}
}

int main()
{
	Printable::PrintHeader("Welcome to the Age of Sigmar BattleSim v" + std::to_string(version), 0);

	//Initialisation
	FactionTable FacTable;
	bool parse = ParseData(FacTable);
	if (!parse) return EXIT_FAILURE;
	CreateDirectoryA("records", NULL);

	//Begin menu loop.
	std::string input;
	
	while (1)
	{
		input.clear();
		PrintMainMenu();

		std::cin >> input;
		switch (static_cast<TopMenuOptions>(std::stoi(input)))
		{
		case(FightSingle):
			std::cout << "Sorry this ain't available yet." << std::endl;
			break;
		case(FightBatch):
			BatchBattle(FacTable);
			break;
		case(Encyclopaedia):
			Encyclopedia(FacTable);
			break;
		case (Exit):
			return EXIT_SUCCESS;
			break;
		default:
			std::cout << "Invalid Entry!" << std::endl;
			break;
		}
	}
    return EXIT_SUCCESS;
}