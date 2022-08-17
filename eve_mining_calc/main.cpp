#include<iostream>
#include <conio.h>
#include"Data.h"
#include"Pilot.h"
#include"Processor.h"


int main(int argc, char** argv)
{
	Data data("config.conf");
	PilotSet pilots;
	Processor processor;

	processor.GetPilotMinedData(&pilots, &data);
	processor.ApplyTaxes(&pilots, &data);
	processor.GetPilotProcessedMaterial(&pilots, &data);

	processor.WriteToFile(&pilots, &data);

	if (data.config.debug)
	{
		data.PrintConfig();
		data.PrintOres();
		data.PrintRaw();
		
		for (auto pilot : pilots) pilot->Print();

		std::cout << "Press any key to close...";
		_getch();
	}

	return 0;
}