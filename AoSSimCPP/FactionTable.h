#include "stdafx.h"

#include "Weapon.h"
#include "Model.h"
#include "Faction.h"

#include "./PugiXML/pugixml.hpp"
#include "./PugiXML/pugiconfig.hpp"

class FactionTable
{
private:
	std::map<std::string, Faction*> *Factions;

public:
	FactionTable();
	~FactionTable();
	
	//Populate with all data pertaining to a faction found in the factions_list.xml file via main();
	void AddFaction(std::string);
	int GetCount() { return Factions->size(); }

	//Get data.
	Faction* GetFaction(std::string);
	Weapon* GetWeapon(std::string, std::string);
	Model* GetModel(std::string, std::string);

	void ListAll();
	void ListFaction(std::string facname);
};
