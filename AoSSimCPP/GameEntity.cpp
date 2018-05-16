#include "stdafx.h"
#include "GameEntity.h"

/*
* GameEntity.cpp: Contains anything common to game entities, e.g. models, weapons.
*/

GameEntity::GameEntity()
{
}

GameEntity::GameEntity(std::string name, std::string faction) : Name(name), Faction(faction)
{
}

GameEntity::~GameEntity()
{
}

bool GameEntity::operator==(const GameEntity& other)
{
	auto myName = Name.begin();
	auto otherName = other.Name.begin();

	while (myName != Name.end() && otherName != other.Name.end())
	{
		try { if (tolower(*myName) != tolower(*otherName)) return false; }
		catch (std::exception e) { return false; }
		myName, otherName++;
	}
	return true;
}