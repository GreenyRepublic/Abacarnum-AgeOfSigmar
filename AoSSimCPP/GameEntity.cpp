#include "stdafx.h"
#include "GameEntity.h"

/*
* GameEntity.cpp: Contains anything common to game entities, e.g. models, weapons.
* Only has name information right now, might change later, might not.
*/

GameEntity::GameEntity()
{
	//std::cout << "Default constructor called!" << std::endl;
}

GameEntity::GameEntity(std::string name)
{
	//std::cout << "Name constructor called! (" << name << ")" << std::endl;
	Name = name;
	FormName = Standardise(name);
}


GameEntity::~GameEntity()
{
}

std::string GameEntity::GetName(bool standardised = false)
{
	if (standardised) return FormName;
	return Name;
}

//Removes capitals and spaces from an entity name for a standardised lookup format.
std::string GameEntity::Standardise(std::string in)
{
	int i = 0;
	std::string result;
	while (in[i] != NULL) {
		const char c = (char)tolower(in[i]);
		if (in[i] != ' ') result += c;
		i++;
	}
	return result;
}