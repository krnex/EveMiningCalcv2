#pragma once
#include<map>
#include"Data.h"
#include"Help.h"

#define PilotSet std::vector<Pilot*>

class Pilot
{
public:
	Pilot(std::vector<std::string> alias);
	~Pilot();

	void AddOreMined(std::string oreName, int oreNumber);
	void SetOresMined(Ore ore);

	bool IsAlias(std::string alias);
	void Print();

private:
	std::vector<std::string> alias;
	Ore oresMined;
};
