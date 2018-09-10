#pragma once
#include "GameEntity.h"

//Stuff to help with special abilities

enum ModOperation {
	Sum = 0,
	Multiply,
	Divide,
	Assign
};

//for Modifiers, these contain near-identical data to stats, with the caveat that they may only last some amount of time, and also contain an operator.
//E.g. 'Unit X casts debuff on Unit Y that halves its health and subtracts 1 from rend' - This can get confusing quickly if you just pass primitive data types.
struct Modifier : GameEntity
{
	int duration = 0;
	ModOperation type;
	void PrintStats();
	void EndTurn();
};

struct Attack
{
	size_t wounds,
		rend,
		damage;

	Attack(size_t w, size_t r, size_t d) : wounds(w), rend(r), damage(d)
	{};
};

template <typename A>
struct Predicate
{
	bool operator()(A lhs, A rhs, std::binary_function<A, A, bool> func)
	{
		return func(lhs, rhs);
	}
};


class Ability
{
private:
	std::string name;
	size_t duration, turnsLeft;
	virtual bool Predicate() = 0;
	ModOperation operation;

public:
	virtual void Evaluate() = 0;
	Ability();
	virtual ~Ability();
};

class DefensiveAbility : Ability
{
public:
	void Evaluate(Attack&);
};