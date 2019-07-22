#include "stdafx.h"
#include "PrintData.h"

//Pretty ascii art for titles and whatnot.


void PrintData::PrintHeader(std::string title, HeaderLevel level)
{
	switch (level)
	{
	case BoxHeader:
		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;
		std::cout << "|| " << title << " ||" << std::endl;
		std::cout << "==-";
		for (auto c = title.begin(); c != title.end(); c++)	std::cout << "-";
		std::cout << "-==" << std::endl;
		break;

	case TopLine:
		std::cout << "|<>| " << title << " |<>|" << std::endl;
		break;

	case LowLevel:
		std::cout << "|==| " << title << " |==|" << std::endl;
		break;

	default:
		break;
	}
}

std::string PrintData::ToUpper(std::string in)
{
	if (in.empty()) return  "";
	else
	{
		return static_cast<char>(toupper(in.at(0))) + ToUpper(in.substr(1));
	}
}