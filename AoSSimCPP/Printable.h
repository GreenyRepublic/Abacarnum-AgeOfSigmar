#pragma once
#include "stdafx.h"



//Provides abstract interface for anything that has printable stats
class Printable
{
	protected:
		std::string ToUpper(std::string);

	public:
		virtual void PrintStats() = 0;
		static void PrintHeader(std::string, int);
};