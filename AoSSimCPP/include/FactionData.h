#pragma once
#include "stdafx.h"
#include "DataWriter.h"

class FactionData
{
public:
	FactionData(std::string name, std::string grandalliance = "");
	~FactionData();

	std::string GetName() const { return FactionName; }
	std::string GetGrandAlliance() const { return GrandAlliance; }

	//Get model/weapon profiles by name.
	ModelProfile GetModelProfile( const std::string) const;

	int operator<(const FactionData& rhs) { return FactionName < rhs.FactionName; }

private:
	friend class DataWriter;
	friend class FactionTable;

	void AddModelProfile(const ModelProfile& model);

	std::unordered_map<std::string, const ModelProfile> FactionModels;
	std::string FactionName;
	std::string GrandAlliance;
};

