#pragma once

static class Die {
public:
	Die(int s = 6);
	~Die();
	static int Roll(int mods = 0);

private:
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> dist;
};

