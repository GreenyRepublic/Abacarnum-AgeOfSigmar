#pragma once

struct ModelProfile
{
	//Unit Stats
	size_t move{ 0 };
	size_t save{ 0 };
	size_t bravery{ 0 };
	size_t wounds{ 0 };
	size_t currentWounds{ 0 };

	ModelProfile(size_t m, size_t s, size_t b, size_t w) :
		move(m), save(s), bravery(b), wounds(w), currentWounds(w) {};
};

struct WeaponProfile
{
	//Weapon Stats
	size_t range{ 0 };
	size_t attacks{ 0 };
	size_t tohit{ 0 };
	size_t towound{ 0 };
	size_t rend{ 0 };
	size_t damage{ 0 };

	WeaponProfile(size_t r, size_t a, size_t h, size_t w, size_t n, size_t d) :
		range(r), attacks(a), tohit(h), towound(w), rend(n), damage(d) {};
	WeaponProfile() {};
};