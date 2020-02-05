// AoSSimCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Die.h"
#include "Weapon.h"
#include "Model.h"
#include "FactionTable.h"
#include "Unit.h"
#include "Battle.h"
#include "DataWriter.h"
#include "MenuOptions.h"
#include "AoSSim.h"

static constexpr float version = 0.6;

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


void AOSsim::SingleBattle()
{
	Battle battle;

	battle.SetUnit(FactionTable::GetInstance()->FindModel("Saurus Warriors (Clubs)"), 10, Attacker);
	battle.SetUnit(FactionTable::GetInstance()->FindModel("Liberators (Warhammer and Shield)"), 20, Defender);

	battle.SingleBattle();
}

void AOSsim::BatchBattle()
{
	Battle battle;

	battle.SetUnit(FactionTable::GetInstance()->FindModel("Saurus Warriors (Clubs)"), 10, Attacker);
	battle.SetUnit(FactionTable::GetInstance()->FindModel("Liberators (Warhammer and Shield)"), 20, Defender);

	battle.BatchBattle();
}

//Options for navigating encyclopedia entries
void AOSsim::Encyclopedia()
{
	FactionTable::GetInstance()->Encyclopedia();
}

void AOSsim::Exit()
{
	exit(1);
}

size_t AOSsim::MainLoop()
{
	DataWriter::PrintAppTitle(version);

	//Initialise database
	FactionTable::GetInstance()->InitialiseFactionTableFromFiles();
	CreateDirectoryA("records", NULL);

	//Begin menu loop.
	CREATE_NUMBERED_MENU(MainMenu, void,
		std::initializer_list<MenuOption>({
			{ MenuOption(std::string("Fight Single Battle"),	[=]() {this->SingleBattle(); })},
			{ MenuOption(std::string("Fight Batch Battle"),		[=]() {this->BatchBattle(); }) },
			{ MenuOption(std::string("Encyclopedia"),			[=]() {this->Encyclopedia(); } ) },
			{ MenuOption(std::string("Exit"),					[=]() {this->Exit(); }) }
			}));

	std::string input;
	while (true)
	{
		MainMenu.PrintMenu();

		input.clear();
		std::cin >> input;
		MainMenu((int)std::stoi(input));
	}

	return EXIT_SUCCESS;
}

int main()
{
	AOSsim sim;
	return sim.MainLoop();
}
