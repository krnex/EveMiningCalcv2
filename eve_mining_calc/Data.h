#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>  
#include "DataValue.h"

class Data
{
public:
	Data();
	~Data();
	int OpenFile(std::string path);

private:
	std::vector<std::vector<std::string>> raw;
};
