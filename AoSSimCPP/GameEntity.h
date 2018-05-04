#pragma once

#include "stdafx.h"
#include <algorithm>
#include <string> 

/* 
* GameEntity: Abstract class
* Defines anything that has a name and belongs to some faction and can be stored in some database
*/

class GameEntity
{
protected:
	std::string Name;
	std::string Faction;

public:
	GameEntity();
	GameEntity(std::string, std::string);
	virtual ~GameEntity();
	
	std::string GetName() { return Name; }
	std::string GetFaction() { return Faction; }
	virtual void EndTurn() = 0; //Triggers end-turn updates
	virtual void PrintStats() = 0; 

	bool operator ==(const GameEntity&); //Case-insensitive equality operator
};

