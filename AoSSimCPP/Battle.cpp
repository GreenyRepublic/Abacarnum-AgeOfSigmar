#include "stdafx.h"
#include "Battle.h"


Battle::Battle(Unit* unita, Unit* unitb, int frontage)
{
	UnitA = unita;
	UnitB = unitb;
	Frontage = frontage;
}


Battle::~Battle()
{
}

//Fight turn-by-turn until one side is wiped out.
void Battle::Fight()
{
	Unit* firstSide = UnitA;
	Unit* secondSide = UnitB;

	std::cout << "COMBAT" << std::endl;
	std::cout << firstSide->GetName() << std::endl;
	std::cout << secondSide->GetName() << std::endl;

	Unit* mostLosses;

	while(1)
	{

		std::cout << firstSide->GetName() << ": " << firstSide->LiveCount() << " remaining." << std::endl;
		std::cout << secondSide->GetName() << ": " << secondSide->LiveCount() << " remaining." << std::endl;

		//Combat
		int w = firstSide->MeleeAttack(secondSide, Frontage);
		std::cout << firstSide->GetName() << " does " << w << " wounds." << std::endl;
		if (secondSide->TakeWounds(w))
		{
			Winner = firstSide;
			break;
		}

		w = secondSide->MeleeAttack(firstSide, Frontage);
		std::cout << secondSide->GetName() << " does " << w << " wounds." << std::endl;
		if (firstSide->TakeWounds(w))
		{
			Winner = secondSide;
			break;
		}

		//Battleshock
		mostLosses = (firstSide->GetLosses() > secondSide->GetLosses()) ? firstSide : secondSide;
		if (mostLosses->Battleshock())
		{
			Winner = (mostLosses == firstSide) ? secondSide : firstSide;
			break;
		}

		firstSide->NewTurn();
		secondSide->NewTurn();

		std::swap(firstSide, secondSide);
	}

	Survivors = Survivors = Winner->LiveCount();
	std::cout << "Winner: " << Winner->GetName() << " with " << Survivors << " models remaining!" << std::endl;
}