// stdafx.cpp : source file that includes just the standard includes
// AoSSimCPP.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//Pretty ascii art for titles and whatnot.
//Levels: 1 = fanciest (top-level header), 3 = least fancy (lowest-level header).
void PrintHeader(std::string title, int level)
{
	std::cout << "==-";
	for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
	std::cout << "-==" << std::endl;

	std::cout << "|| " << title << " ||" << std::endl;

	std::cout << "==-";
	for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
	std::cout << "-==" << std::endl;
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