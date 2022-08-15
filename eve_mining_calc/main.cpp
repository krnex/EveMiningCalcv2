#include<iostream>
#include"Data.h"
#include"Pilot.h"
#include"Processor.h"


int main(int argc, char** argv)
{
	Data data("config.conf");
	PilotSet pilots;
	Processor processor;

	processor.GetPilotData(&pilots, &data);

	if (data.config.debug)
	{
		data.PrintConfig();
		data.PrintOres();
		//data.PrintRaw();
		
		for (auto pilot : pilots) pilot->Print();
	}

	return 0;
}