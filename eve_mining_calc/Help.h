#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<array>
#include <string>
#include <stdio.h>
#include <time.h>

#define Ore std::map<std::string, int>

struct Config
{
	std::string fileName;
	std::vector<std::vector<std::string>> pilots;
	std::array<float, 5> taxrate; // R4, R8, R16, R32, R64
	std::array<float, 3> reprocess; // Ore, Gas, Scrap
	bool debug;
	bool zeroOrePilots;
	bool processedOre;
};

struct OreSection
{
	std::array<std::string, 4> type;
	std::array<std::vector<std::string>, 4> refinedTypes;
	std::vector<int> refinedValues;
	std::array<int, 4> pyeModifer;
	std::array<std::string, 3> modifier;
	float taxrate;
	const std::array<float, 3> REFINING_RATE = {1.0f, 1.15f, 2.0f };
};

bool isSpace(unsigned char c);
std::string ltrim(std::string str);
std::string rtrim(std::string str);
std::string trim(std::string str);
std::vector<std::string> splitOreName(std::string string, char delim);

const std::string currentDateTime();