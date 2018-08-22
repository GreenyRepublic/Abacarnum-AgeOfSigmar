#include "stdafx.h"
#include "Printable.h"

//Pretty ascii art for titles and whatnot.
//Levels: 1 = Box header 
//		  2 = Top-level Line header
//		  3 = Low-level line header
//		  4 = 
void Printable::PrintHeader(std::string title, int level)
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

std::string Printable::ToUpper(std::string in)
{
	if (in.empty()) return  "";
	else
	{
		return static_cast<char>(toupper(in.at(0))) + ToUpper(in.substr(1));
	}
}