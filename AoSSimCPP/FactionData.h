#pragma once
#include "stdafx.h"
#include "Weapon.h"
#include "Model.h"
#include "DataWriter.h"

class FactionData
{
public:
	FactionData(std::string name, std::string grandalliance = "");
	~FactionData();

	void AddWeapon(std::shared_ptr<Weapon>);
	void AddModel(std::shared_ptr<Model>);

	std::string GetName() const { return Name; }
	std::string GetGrandAlliance() const { return GrandAlliance; }

	//Get model/weapon profiles by name.
	std::shared_ptr<Weapon> GetWeapon(std::string) const;
	std::shared_ptr<Model> GetModel(std::string) const;

	int operator<(const FactionData& rhs) { return Name < rhs.Name; }

private:
	friend class DataWriter;

	std::unordered_map<std::string, std::shared_ptr<Weapon>> weaponData;
	std::unordered_map<std::string, std::shared_ptr<Model>> modelData;
	std::string Name;
	std::string GrandAlliance;
};

