#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <cstring>
#include "DataValue.h"

struct Config
{
	std::string fileName;
	std::vector<std::vector<std::string>> pilots;
	std::array<float, 5> taxrate;
	bool debug;
};

struct OreSection
{
	std::array<std::string, 4> type;
	std::array<std::string, 3> modifier;
	float taxrate;
	// Add refining
	const std::array<float, 2> REFINING_RATE = { 1.15f, 2.0f };
};

class Data
{
public:
	Data(std::string path);
	~Data();
	int OpenRawFile(std::string path);
	int OpenConfigFile(std::string path);

	bool IsDebug();
	void PrintConfig();
	void PrintOres();
	void PrintRaw();

private:
	std::vector<std::vector<std::string>> raw;
	Config config;
	std::vector<OreSection> ore;
};
