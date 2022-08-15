#include "Pilot.h"

Pilot::Pilot(std::vector<std::string> alias)
{
	this->alias = alias;
}

Pilot::~Pilot()
{
}

void Pilot::AddOreMined(std::string oreName, int oreNumber)
{
	try
	{
		this->oresMined.at(oreName) += oreNumber;
	}
	catch (const std::out_of_range& oor)
	{
		this->oresMined.insert({oreName, oreNumber});
	}
}

void Pilot::SetOresMined(Ore ore)
{

	for (const auto& value : ore)
	{
		try
		{
			this->oresMined.at(value.first) += value.second;
		} 
		catch (const std::out_of_range& oor)
		{
			this->oresMined.insert(value);
		}
	}

}

bool Pilot::IsAlias(std::string alias)
{
	bool is = false;

	for (auto name : this->alias)
		if (name == alias) is = true;

	return is;
}

void Pilot::Print()
{
	std::cout << "Pilot Alias':" << this->alias[0];
	for (int i = 1; i < this->alias.size(); i++)
	{
		std::cout << ", " << this->alias[i];
	}
	std::cout << std::endl;
	std::cout << "Ores Mined:" << std::endl;
	for (const auto& value : this->oresMined) 
	{
		std::cout << "\t" << value.first << ":\t" << value.second << std::endl;
	}

	std::cout << std::endl;
}