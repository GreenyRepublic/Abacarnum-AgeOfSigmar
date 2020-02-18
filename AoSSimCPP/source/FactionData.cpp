#include "stdafx.h"
#include "FactionData.h"
#include "types/ProfileTypes.h"

FactionData::FactionData(std::string name, std::string grandalliance)
	: FactionName(name),
	GrandAlliance(grandalliance)
{}

FactionData::~FactionData()
{
}

void FactionData::AddModelProfile( const ModelProfile& model )
{
	FactionModels.insert(std::pair<std::string, ModelProfile>(model.name, model));
}

ModelProfile FactionData::GetModelProfile(const std::string name) const
{
	return FactionModels.at(name);
}