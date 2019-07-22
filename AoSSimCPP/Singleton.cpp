#include "stdafx.h"
#include "Singleton.h"

Singleton* Singleton::getInstance()
{
	static Singleton myInstance;
	return &myInstance;
}