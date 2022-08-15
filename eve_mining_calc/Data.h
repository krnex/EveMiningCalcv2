#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstring>
#include "DataValue.h"
#include "Help.h"


class Data
{
public:
	Data(std::string path);
	~Data();
	int OpenRawFile(std::string path);
	int OpenConfigFile(std::string path);

	void PrintConfig();
	void PrintOres();
	void PrintRaw();

	std::vector<std::vector<std::string>> raw;
	std::vector<OreSection> ore;
	Config config;
private:
};
