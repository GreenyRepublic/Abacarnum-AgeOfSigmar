#include "stdafx.h"
#include "Battle.h"

//Fight turn-by-turn until one side is wiped out.
BattleStats Battle(Unit* unita, Unit* unitb, int frontage)
{
	Unit* firstSide = unita;
	Unit* secondSide = unitb;
	Unit* Winner;

	int survivors;
	int turns = 0;

	//std::cout << "COMBAT" << std::endl;
	//std::cout << firstSide->GetName() << std::endl;
	//std::cout << secondSide->GetName() << std::endl;


	Unit* mostLosses;

	while(1)
	{
		turns++;
		//std::cout << firstSide->GetName() << ": " << firstSide->LiveCount() << " remaining." << std::endl;
		//std::cout << secondSide->GetName() << ": " << secondSide->LiveCount() << " remaining." << std::endl;

		//Combat
		int w = firstSide->MeleeAttack(secondSide, frontage);
		//std::cout << firstSide->GetName() << " does " << w << " wounds." << std::endl;
		if (secondSide->TakeWounds(w))
		{
			Winner = firstSide;
			break;
		}

		w = secondSide->MeleeAttack(firstSide, frontage);
		//std::cout << secondSide->GetName() << " does " << w << " wounds." << std::endl;
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

	survivors = Winner->LiveCount();
	bool win = (Winner == unita) ? true : false;
	//std::cout << "Winner: " << Winner->GetName() << " with " << survivors << " models remaining!" << std::endl;

	return BattleStats{ win, unita->GetName(), unitb->GetName(), survivors, turns };
}