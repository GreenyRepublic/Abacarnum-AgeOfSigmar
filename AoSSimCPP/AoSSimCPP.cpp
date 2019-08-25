// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Die.h"
#include "Weapon.h"
#include "Model.h"
#include "FactionTable.h"
#include "Unit.h"
#include "Battle.h"
#include "PrintData.h"

static constexpr char * version = "0.6";

//Crunches battle stats and writes to file.
/*void WriteStats(std::vector<BattleStats>& stats, std::string aname, std::string bname, size_t amodels, size_t bmodels)
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

	file << "unit,noOfModels,winCount,winRate,avgSurvivorsPerWin,avgTurnsPerBattle\n";
	file << ",,,,," << turns << "\n";
	file << aname << ',' << amodels << ',' << WinNum << ',' << (100 * WinNum / stats.size()) << "%," << survivors[aname] << '\n';
	file << bname << ',' << bmodels << ',' << battlenum - WinNum << ',' << (100.0 - (100 * WinNum / stats.size())) << "%," << survivors[bname];
	
	file.close();
}*/

void SingleBattle(){}

void BatchBattle(){}

void Exit()
{
	exit(1);
}

std::vector<std::string> TopMenuStrings{
	"Fight Single Battle", 
	"Fight Batch Battles", 
	"Encyclopaedia", 
	"Exit"
};

enum TopMenuOption
{
	MenuOptionFightSingle = 1,
	MenuOptionFightBatch,
	MenuOptionEncyclopedia,
	MenuOptionExit,

	TotalOptions
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
void Encyclopedia()
{
	std::string input;
	unsigned int opt;
	while (1)
	{
		FactionTable::GetInstance()->ListAllFactions(true);
		std::cout << "Enter a faction number or name for a full list of models, or enter '0' to return to the main menu." << std::endl;
		std::cin >> input;
		opt = std::stoi(input);

		if (opt == 0) return;
		else (FactionTable::GetInstance()->PrintFactionData(opt));
	}
}

static std::map< TopMenuOption, void(*)(void) > MenuOptionsTable
{
	{ TopMenuOption::MenuOptionFightSingle, SingleBattle },
	{ TopMenuOption::MenuOptionFightBatch, BatchBattle },
	{ TopMenuOption::MenuOptionEncyclopedia, Encyclopedia },
	{ TopMenuOption::MenuOptionExit, Exit }

};

int main()
{
	PrintData::PrintHeader("Welcome to the Age of Sigmar BattleSim v" + std::string(version), HeaderLevel::BoxHeader);

	//Initialisation
	FactionTable::GetInstance()->InitialiseFactionTableFromFiles();
	CreateDirectoryA("records", NULL);

	//Begin menu loop.
	std::string input;
	while (true)
	{
		input.clear();
		PrintMainMenu();

		std::cin >> input;
		TopMenuOption opt;
		try
		{
			opt = static_cast<TopMenuOption>(std::stoi(input));
		}
		catch (std::invalid_argument e)
		{
			std::cout << "Invalid entry!" << std::endl;
		}
		MenuOptionsTable[opt]();
	}
    return EXIT_SUCCESS;
}