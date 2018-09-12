#pragma once
#include "GameEntity.h"

//Stuff to help with special abilities

enum ModOperation {
	Sum,
	Multiply,
	Divide,
	Assign
};

enum AttackType
{
	Melee,
	Ranged,
	Magical
};

//for Modifiers, these contain near-identical data to stats, with the caveat that they may only last some amount of time, and also contain an operator.
//E.g. 'Unit X casts debuff on Unit Y that halves its health and subtracts 1 from rend' - This can get confusing quickly if you just pass primitive data types.
struct Modifier : GameEntity
{
	int Duration = 0;
	ModOperation Type;
	void PrintStats();
	void EndTurn();
};

struct Attack
{
	AttackType Type;
	size_t Wounds,
		Rend,
		Damage;

	Attack(size_t w, size_t r, size_t d, AttackType t) : Wounds(w), Rend(r), Damage(d), Type(t) {};
};

struct Battleshock
{
	size_t Losses;
	Battleshock(size_t l) : Losses(l) {};
};

template <typename T>
struct Predicate
{
	bool operator()(T lhs, T rhs, std::binary_function<T, T, bool> func)
	{
		return func(lhs, rhs);
	}
};

template <typename T>
class Ability : public GameEntity
{
private:
	size_t Duration;
	ModOperation Operation;

public:
	virtual void operator()(T&) = 0;
	void EndTurn();
};

class DefensiveAbility : Ability<Attack>
{
public:
	void operator()(Attack&);
};
class OffensiveAbility : Ability<Attack>
{
};
class BattleshockAbility : Ability<Battleshock>
{};