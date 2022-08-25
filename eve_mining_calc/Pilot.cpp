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

void Pilot::AddOreSetMined(Ore ore)
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

void Pilot::ApplyTaxes(Data* data)
{
	for (auto& value : this->oresMined)
	{
		std::vector<std::string> splitName = splitOreName(value.first, ' ');

		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (data->ore[i].type[k] == splitName[1])
				{
					value.second = value.second * (1.0f - data->ore[i].taxrate);
					break;
				}
			}
		}

	}
}

void Pilot::ProcessOres(Data* data)
{
	this->oresProcessed.clear();

	for (const auto& value : this->oresMined)
	{
		std::vector<std::string> splitName = splitOreName(value.first, ' ');

		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (data->ore[i].type[k] == splitName[1])
				{
					int remaining = value.second % 100;
					for(int l = 0; l < data->ore[i].refinedTypes[k].size(); l++)
					{
						float modifier = 1.0f;
						
						for (int j = 0; j < data->ore[i].modifier.size(); j++)
						{
							if (data->ore[i].modifier[j] == splitName[0])
								modifier = data->ore[i].REFINING_RATE[j];
						}

						std::string name = data->ore[i].refinedTypes[k][l];
						float pyeMod = (name == "Pye" ? data->ore[i].pyeModifer[k] : 1.0f);
						
						float stepOne = float(value.second - remaining) / 100.0f;
						float stepTwo = round((float(data->ore[i].refinedValues[l])) * modifier);

						int quantity = (stepTwo * stepOne * data->config.reprocess[0] * pyeMod);
						
						try
						{
							this->oresProcessed.at(name) += quantity;
						}
						catch (const std::out_of_range& oor)
						{
							this->oresProcessed.insert({name, quantity});
						}
					}

					if (remaining > 0)
					{
						try
						{
							this->oresProcessed.at(value.first) += remaining;
						}
						catch (const std::out_of_range& oor)
						{
							this->oresProcessed.insert({ value.first, remaining });
						}
					}
				}
			}
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

bool Pilot::HasOre()
{
	return (this->oresMined.size() > 0);
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
		std::cout << "\t" << value.first << "\t" << value.second << std::endl;
	}
	std::cout << "Processed Ore:" << std::endl;
	for (const auto& value : this->oresProcessed)
	{
		std::cout << "\t" << value.first << "\t" << value.second << std::endl;
	}

	std::cout << std::endl;
}

