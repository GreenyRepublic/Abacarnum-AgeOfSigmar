#pragma once

/* Interface for Singletons */

class Singleton
{
public:
	static Singleton* getInstance();

private: 
	Singleton() {};

};

