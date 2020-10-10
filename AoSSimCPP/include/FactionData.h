#pragma once
#include "stdafx.h"
#include "DataWriter.h"

class FactionData
{
public:
	FactionData(std::string name, std::string grandalliance = "");
	~FactionData();

	std::string GetName() const { return mFactionName; }
	std::string GetGrandAlliance() const { return mGrandAlliance; }

	const ModelProfile& GetModelProfile( const std::string) const;

	int operator<(const FactionData& rhs) { return mFactionName < rhs.mFactionName; }

private:
	friend class DataWriter;
	friend class FactionDatabase;

	void AddModelProfile(const ModelProfile& model);

	std::unordered_map<std::string, const ModelProfile> mFactionModelProfiles;

	std::string mFactionName;
	std::string mGrandAlliance;
};

