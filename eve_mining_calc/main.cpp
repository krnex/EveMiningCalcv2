#include <iostream>
#include "Data.h"

int main(int argc, char** argv)
{
	Data data("config.conf");

	if (data.config.debug)
	{
		data.PrintConfig();
		data.PrintOres();
		data.PrintRaw();
	}

	return 0;
}