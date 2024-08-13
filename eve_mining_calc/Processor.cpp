#include"Processor.h"

Processor::Processor()
{
}

Processor::~Processor()
{
}

void Processor::GetPilotMinedData(PilotSet* pilots, Data* data)
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

void Processor::ApplyTaxes(PilotSet* pilots, Data* data)
{
	for (auto pilot : *pilots)
	{
		pilot->ApplyTaxes(data);
	}
}

void Processor::GetPilotProcessedMaterial(PilotSet* pilots, Data* data)
{
	for (auto pilot : *pilots)
	{
		pilot->ProcessOres(data);
	}

}

void Processor::WriteToFile(PilotSet* pilots, Data* data)
{
	std::ofstream out(currentDateTime() + ".txt");

	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	for (auto pilot : *pilots)
	{
		if(data->config.zeroOrePilots || pilot->HasOre())
			pilot->Print(true, true, data->config.processedOre);
	}

	std::cout.rdbuf(coutbuf);
}