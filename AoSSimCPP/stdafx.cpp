// stdafx.cpp : source file that includes just the standard includes
// AoSSimCPP.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//Pretty ascii art for titles and whatnot.
//Levels: 1 = Box header 
//		  2 = Top-level Line header
//		  3 = Low-level line header
//		  4 = 
void PrintHeader(std::string title, int level)
{
	if (level == 1)
	{
		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;

		std::cout << "|| " << title << " ||" << std::endl;

		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;
	}

	else if (level == 2)
	{
		std::cout << "|<>| " << title << " |<>|" << std::endl;
	}

	else if (level == 3)
	{
		std::cout << "|==| " << title << " |==|" << std::endl;
	}
}

char UpperChar(char in)
{
	return toupper(in);
}

std::string ToUpper(std::string in)
{
	if (in.empty()) return  "";
	else
	{
		return UpperChar(in.at(0)) + ToUpper(in.substr(1));
	}
}