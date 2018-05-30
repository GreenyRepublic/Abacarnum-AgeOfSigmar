#include "stdafx.h"
#include "Battle.h"

//Fight turn-by-turn until one side is wiped out.
BattleStats Battle(Unit& unita, Unit& unitb, int frontage)
{
	Unit& SideA = unita;
	Unit& SideB = unitb;
	Side Winner;
	int survivors;
	int turns = 0;

	//std::cout << "COMBAT" << std::endl;
	//std::cout << firstSide->GetName() << std::endl;
	//std::cout << secondSide->GetName() << std::endl;

	while(1)
	{
		//std::cout << firstSide->GetName() << ": " << firstSide->LiveCount() << " remaining." << std::endl;
		//std::cout << secondSide->GetName() << ": " << secondSide->LiveCount() << " remaining." << std::endl;

		//Combat
		if (turns % 2 == 0)
		{
			SideA.MeleeAttack(SideB, frontage);
			SideB.MeleeAttack(SideA, frontage);
		}
		else
		{
			SideB.MeleeAttack(SideA, frontage);
			SideA.MeleeAttack(SideB, frontage);
		}
		
		//Battleshock
		if (SideA.GetLosses() > SideB.GetLosses()) SideA.Battleshock();
		else if (SideA.GetLosses() < SideB.GetLosses()) SideB.Battleshock();

		if (SideA.GetLive() == 0)
		{
			Winner = Side::SideB;
			survivors = SideB.GetLive();
			break;
		}

		else if (SideB.GetLive() == 0)
		{
			Winner = Side::SideA;
			survivors = SideA.GetLive();
			break;
		}

		turns++;
	}

	return BattleStats{Winner, survivors, turns };
}