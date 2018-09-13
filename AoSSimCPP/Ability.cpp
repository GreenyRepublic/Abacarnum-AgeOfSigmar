#include "stdafx.h"
#include "Ability.h"

template <typename T>
void Ability<T>::EndTurn()
{
	if (Duration == 1) delete(this);
	Duration--;
}

template <typename T>
void Ability<T>::operator()(T&)
{
	if (Predicate())
}