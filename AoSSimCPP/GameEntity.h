#pragma once

#include "stdafx.h"

/* 
* GameEntity: Abstract class
* Defines anything that has a name and belongs to some faction and can be stored in some database
*/

class GameEntity
{
protected:
	std::string Name;
	std::string FormName;
	std::string Standardise(std::string in);

public:
	GameEntity();
	GameEntity(std::string);
	virtual ~GameEntity();

	virtual void PrintStats() = 0;
	std::string GetName(bool);
};

