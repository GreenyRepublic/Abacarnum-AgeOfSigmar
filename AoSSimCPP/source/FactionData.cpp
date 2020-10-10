#include "stdafx.h"
#include "FactionData.h"
#include "types/ProfileTypes.h"

FactionData::FactionData(std::string name, std::string grandalliance)
	: mFactionName(name),
	mGrandAlliance(grandalliance)
{}

FactionData::~FactionData()
{
}

void FactionData::AddModelProfile( const ModelProfile& model )
{
	mFactionModelProfiles.insert(std::pair<std::string, ModelProfile>(model.mName, model));
}

const ModelProfile& FactionData::GetModelProfile(const std::string name) const
{
	return mFactionModelProfiles.at(name);
}