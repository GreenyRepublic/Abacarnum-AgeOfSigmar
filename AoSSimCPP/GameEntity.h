#pragma once

#include "stdafx.h"
#include <algorithm>
#include <string> 

/* 
* GameEntity: Abstract class
* Defines any entity that exists 'on the table' in a game, whether literal or abstract.
* Examples include units, models, weapons, and abilities.
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
	virtual void EndTurn() = 0; //Resolve end-turn updates
	virtual void PrintStats() = 0; //Prints information to the console

	bool operator ==(const GameEntity&); //Case-insensitive name comparison operator
};

