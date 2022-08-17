#pragma once
#include"Pilot.h"
#include"Data.h"
#include"DataValue.h"

class Processor
{
public:
	Processor();
	~Processor();

	void GetPilotMinedData(PilotSet* pilots, Data* data);
	void GetPilotProcessedMaterial(PilotSet* pilots, Data* data);
	void ApplyTaxes(PilotSet* pilots, Data* data);

	void WriteToFile(PilotSet* pilots, Data* data);

private:

};
