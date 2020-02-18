#pragma once
#include "stdafx.h"

/* 
* GameEntity: Abstract class
* Defines any entity that exists 'on the table' in a game, whether literal or abstract.
* Examples include units, models, weapons, and abilities.
*/

class GameEntity
{
private:
	static size_t sEntityCount;
	size_t mEntityID;

protected:
	std::string mEntityName;
	std::string mEntityFaction;

public:
	GameEntity(std::string name, std::string faction = "");
	virtual ~GameEntity();
	
	const std::string GetName() const { return mEntityName; }
	const std::string GetFaction() const { return mEntityFaction; }
	const size_t GetEntityID() const { return mEntityID; }

	virtual void EndTurn() = 0; //Resolve end-turn updates

	bool operator ==( const GameEntity& ); //Case-insensitive name comparison operator
};

