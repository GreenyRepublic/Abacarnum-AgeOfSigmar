
#include "stdafx.h"

#include "Die.h"
#include "FactionDatabase.h"
#include "Unit.h"
#include "Battle.h"
#include "DataWriter.h"

// WxWidgets
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif


static constexpr float version = 0.8;

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

class Abacarnum : public wxApp
{
public:
	virtual bool OnInit() wxOVERRIDE;
	void SingleBattle();
	void BatchBattle();
	void Exit();
	//int MainLoop();
};

class MainWindow : public wxFrame
{
public:
	// ctor(s)
	MainWindow(const wxString& title);

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};


//wxWidgets Options
enum {
	aosQuit = wxID_EXIT,
	aosAbout = wxID_ABOUT
};


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_MENU(aosQuit, MainWindow::OnQuit)
	EVT_MENU(aosAbout, MainWindow::OnAbout)
wxEND_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(Abacarnum);

bool Abacarnum::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}

	// create the main application window
	MainWindow *window = new MainWindow("AoS Sim");

	window->Show(true);

	return true;
}

void Abacarnum::SingleBattle()
{
	Battle battle = Battle();

	battle.SetUnit(FactionDatabase::GetFactionDatabase()->GetModelProfile("Saurus Warriors (Clubs)"), 20, Side::Attacker);
	battle.SetUnit(FactionDatabase::GetFactionDatabase()->GetModelProfile("Liberators (Warhammer and Shield)"), 10, Side::Defender);

	battle.SingleBattle();
}

void Abacarnum::BatchBattle()
{
	Battle battle = Battle();

	battle.SetUnit(FactionDatabase::GetFactionDatabase()->GetModelProfile("Saurus Warriors (Clubs)"), 20, Side::Attacker);
	battle.SetUnit(FactionDatabase::GetFactionDatabase()->GetModelProfile("Liberators (Warhammer and Shield)"), 10, Side::Defender);

	battle.BatchBattle();
}

void Abacarnum::Exit()
{
	exit(1);
}


MainWindow::MainWindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	wxMenu* fileMenu = new wxMenu;
	wxMenu* helpMenu = new wxMenu;
	fileMenu->Append(aosQuit, "Quit");
	helpMenu->Append(aosAbout, "About");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar(2);
	SetStatusText("Welcome to AoSSim!");
}

void MainWindow::OnQuit(wxCommandEvent& event)
{
	Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxString::Format
	(
		"Welcome to %s!\n"
		"\n"
		"This is the minimal wxWidgets sample\n"
		"running under %s.",
		wxVERSION_STRING,
		wxGetOsDescription()
	),
		"About wxWidgets minimal sample",
		wxOK | wxICON_INFORMATION,
		this);
}
