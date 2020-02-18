#include "stdafx.h"
#include "GameEntity.h"

/*
* GameEntity.cpp: Contains anything common to game entities, e.g. models, weapons.
*/

size_t GameEntity::sEntityCount = 0;

GameEntity::GameEntity(std::string name, std::string faction) : 
	mEntityName(name), 
	mEntityFaction(faction)
{
	mEntityID = sEntityCount++;
}

GameEntity::~GameEntity()
{
}

bool GameEntity::operator==(const GameEntity& other)
{
	auto myName = mEntityName.begin();
	auto otherName = other.mEntityName.begin();

	while (myName != mEntityName.end() && otherName != other.mEntityName.end())
	{
		try { if (tolower(*myName) != tolower(*otherName)) return false; }
		catch (std::exception e) { return false; }
		myName, otherName++;
	}
	return true;
}