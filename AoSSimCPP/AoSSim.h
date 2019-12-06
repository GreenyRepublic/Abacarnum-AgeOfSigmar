#pragma once

class aosSim
{
public:
	void SingleBattle(size_t arg = 0);
	void BatchBattle(size_t arg = 0);
	void Encyclopedia(size_t arg = 0);
	void Exit(size_t arg = 0);
	void MenuLoop();

	static aosSim* getInstance();
};