#pragma once
#include "stdafx.h"


enum HeaderLevel
{
	BoxHeader = 1,
	TopLine,
	LowLevel
};

//Provides some nifty printing stuff
namespace PrintData
{
	std::string ToUpper(std::string);
	void PrintHeader(std::string, HeaderLevel);
}