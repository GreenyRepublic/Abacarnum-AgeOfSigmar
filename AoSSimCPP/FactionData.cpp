#include "stdafx.h"
#include "FactionData.h"

FactionData::FactionData(std::string name, std::string grandalliance)
	: Name(name),
	GrandAlliance(grandalliance)
{}

FactionData::~FactionData()
{
}

void FactionData::AddWeapon(std::shared_ptr<Weapon> weapon)
{
	weaponData.insert(std::pair<std::string, std::shared_ptr<Weapon>>(weapon->GetName(), weapon));
}

void FactionData::AddModel(std::shared_ptr<ModelProfile> model)
{
	modelData.insert(std::pair<std::string, std::shared_ptr<ModelProfile>>(model->GetName(), model));
}

std::shared_ptr<Weapon> FactionData::GetWeapon(std::string name) const
{
	return weaponData.at(name);
}

std::shared_ptr<ModelProfile> FactionData::GetModel(std::string name) const
{
	return modelData.at(name);
}