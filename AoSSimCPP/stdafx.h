// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

#include <Windows.h>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <new>
#include <ios>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <unordered_map>
#include <vector>
#include <random>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <ctype.h>
#include <memory>

extern "C" {
# include "lua_5_3_5/lua.h"
# include "lua_5_3_5/lauxlib.h"
# include "lua_5_3_5/lualib.h"
}

#include "luabridge/LuaBridge.h"

std::string ToUpper(std::string);