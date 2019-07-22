#pragma once
#include "stdafx.h"
//Standard 6-sided die, basically a helper/macro for the <random> lib

class Die
{
public:
	static int RollD3();
	static int RollD6();

private:
	Die() {};
	~Die();
	static std::uniform_int_distribution<unsigned int> dieDistribution;
	static std::default_random_engine dieGenerator;
};
