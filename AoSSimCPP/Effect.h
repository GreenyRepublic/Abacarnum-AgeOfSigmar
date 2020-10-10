#pragma once
#include "stdafx.h"
#include "luabridge/LuaBridge.h"
#include "types/ActionTypes.h"

enum class EffectTrigger
{
	SaveRoll = 0,

};

template <typename T>
class Effect
{
public:
	inline Effect() {};
	inline ~Effect() {};
	inline T Evaluate(T payload)
	{
		luabridge::LuaRef outData = mFunction(payload);
	};
protected:
	luabridge::LuaRef mFunction;
};

class SaveRollEffect : Effect<AttackAction>
{
public:
	SaveRollEffect(luabridge::LuaRef func)
	{
		mFunction = func;
	};

	AttackAction Evaluate(AttackAction payload)
	{

	}
};