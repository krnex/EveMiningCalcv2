#pragma once
#include"Pilot.h"
#include"Data.h"
#include"DataValue.h"

class Processor
{
public:
	Processor();
	~Processor();

	void GetPilotData(PilotSet* pilots, Data* data);

private:

};
