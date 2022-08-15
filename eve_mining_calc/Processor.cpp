#include"Processor.h"

Processor::Processor()
{
}

Processor::~Processor()
{
}

void Processor::GetPilotData(PilotSet* pilots, Data* data)
{
	for (auto pilotNames : data->config.pilots)
	{
		Pilot* newPilot = new Pilot(pilotNames);
		pilots->push_back(newPilot);
	}

	for (auto row : data->raw)
	{
		for (auto pilot : *pilots)
		{
			if (pilot->IsAlias(row[D_PILOT]))
			{
				pilot->AddOreMined(row[D_ORE_TYPE], std::stoi(row[D_QUANTITY]));
			}
		}
	}
}
