#include "stdafx.h"
#include "Battle.h"

//Fight turn-by-turn until one side is wiped out.
BattleStats Battle(Unit unita, Unit unitb, int frontage)
{
	std::string winner;
	int survivors;
	int turns = 0;

	//std::cout << "COMBAT" << std::endl;
	//std::cout << firstSide->GetName() << std::endl;
	//std::cout << secondSide->GetName() << std::endl;

	while(1)
	{
		//std::cout << unita.GetName() << ": " << unita.GetLive() << " remaining." << std::endl;
		//std::cout << unitb.GetName() << ": " << unitb.GetLive() << " remaining." << std::endl;

		//Combat
		if (turns % 2 == 0)
		{
			unita.MeleeAttack(unitb, frontage);
			unitb.MeleeAttack(unita, frontage);
		}
		else
		{
			unitb.MeleeAttack(unita, frontage);
			unita.MeleeAttack(unitb, frontage);
		}
		
		//Battleshock
		if (unita.GetLosses() > unitb.GetLosses()) unita.TakeBattleshock();
		else if (unita.GetLosses() < unitb.GetLosses()) unitb.TakeBattleshock();

		if (unita.GetLive() == 0)
		{
			winner = unitb.GetName();
			survivors = unitb.GetLive();
			return BattleStats{ winner, survivors, turns };
		}

		else if (unitb.GetLive() == 0)
		{
			winner = unita.GetName();
			survivors = unita.GetLive();
			return BattleStats{ winner, survivors, turns };
		}
		turns++;
	}
}