#pragma once

#include "stdafx.h"

//Header for GameEntity.cpp
class GameEntity
{
protected:
	std::string Name;
	std::string FormName;
	std::string Standardise(std::string in);

public:
	GameEntity();
	GameEntity(std::string);
	~GameEntity();

	std::string GetName(bool);
};

