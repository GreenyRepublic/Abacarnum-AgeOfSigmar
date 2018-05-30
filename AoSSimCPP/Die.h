#pragma once
//Standard 6-sided die, basically a helper/macro for the <random> lib

namespace Die {
	static std::uniform_int_distribution<int> distribution;
	static std::default_random_engine generator;

	int Roll(int = 0);
	void initDie();
}
