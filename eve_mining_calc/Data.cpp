#include "Data.h"

bool isSpace(unsigned char c) {
	return (c == ' ' || c == '\n' || c == '\r' ||
		c == '\t' || c == '\v' || c == '\f' || c == '\0');
}

std::string ltrim(std::string str)
{
	if (isSpace(str.back()) && str.size() > 1)
	{
		str.erase(str.size() - 1, 1);
		ltrim(str);
	}

	return str;
}

std::string rtrim(std::string str)
{
	if (isSpace(str[0]) && str.size() > 1)
	{
		str.erase(0, 1);
		ltrim(str);
	}

	return str;
}

std::string trim(std::string str)
{
	str = ltrim(str);
	str = rtrim(str);

	return str;
}

Data::Data(std::string path)
{
	this->OpenConfigFile(path);
	this->OpenRawFile(this->config.fileName);

	OreSection section1 = { 
		{"Bitumens", "Coesite", "Sylvite", "Zeolites"},
		{"", "Brimful", "Glistening"},
		this->config.taxrate[0]
	};

	OreSection section2 = { 
		{"Cobalitite", "Euxenite", "Scheelite", "Titanite"},
		{"", "Copious", "Twinkling" },
		this->config.taxrate[1]
	};

	OreSection section3 = { 
		{"Chromite", "Otavite", "Sperrylite", "Vanadinite"},
		{"", "Lavish", "Shimmering"},
		this->config.taxrate[2]
	};

	OreSection section4 = {
		{"Carnotite", "Cinnabar", "Pollucite", "Zircon"},
		{"", "Glowing", "Replete"},
		this->config.taxrate[3]
	};

	OreSection section5 = {
		{"Loparite", "Monazite", "Xenotime", "Ytterbite"},
		{"", "Bountiful", "Shining"},
		this->config.taxrate[4]
	};

	this->ore.push_back(section1);
	this->ore.push_back(section2);
	this->ore.push_back(section3);
	this->ore.push_back(section4);
	this->ore.push_back(section5);
}

Data::~Data()
{
}

// Possible bug : first line has titles.
int Data::OpenRawFile(std::string path)
{
	int errorValue = 0;

	std::ifstream myfile;
	myfile.open(path);

	std::string myline;

	if (myfile.is_open())
	{
		while (myfile)
		{
			std::vector<std::string> lineData;
			std::getline(myfile, myline);

			std::string value;
			std::stringstream lineToParse(myline);
			while (std::getline(lineToParse, value, '\t'))
			{
				lineData.push_back(value);
			}
			this->raw.push_back(lineData);
		}
	} 
	else 
	{
		std::cout << "Error: Could not read file " << path << std::endl;
		errorValue = 1;
	}


	return errorValue;
}

int Data::OpenConfigFile(std::string path)
{
	int errorValue = 0;

	std::ifstream myfile;
	myfile.open(path);

	std::string myline;

	bool pilots = false;

	if (myfile.is_open())
	{
		while (myfile)
		{
			std::getline(myfile, myline);

			std::vector<std::string> lineData;

			std::string value;
			std::stringstream lineToParse(myline);
			while (std::getline(lineToParse, value, ':'))
			{
				value = trim(value);
				lineData.push_back(value);
			}

			if (lineData.size() <= 0) 
			{
				pilots = false;
				continue;
			}

			if (!pilots)
			{
				if (lineData[0] == "dataPath")
					this->config.fileName = (lineData[1]);

				if (lineData[0] == "debug")
					this->config.debug = lineData[1] == "true" ? true : false;

				if (lineData[0] == "R4")
					this->config.taxrate[0] = std::stof((lineData[1]));
				if (lineData[0] == "R8")
					this->config.taxrate[1] = std::stof((lineData[1]));
				if (lineData[0] == "R16")
					this->config.taxrate[2] = std::stof((lineData[1]));
				if (lineData[0] == "R32")
					this->config.taxrate[3] = std::stof((lineData[1]));
				if (lineData[0] == "R64")
					this->config.taxrate[4] = std::stof((lineData[1]));
				
				if (lineData[0] == "oreRate")
					this->config.reprocess[0] = std::stof((lineData[1]));

				if (lineData[0] == "Pilots")
					pilots = true;

			}
			else if (pilots)
			{

				std::string pilot;
				std::stringstream lineToParse(lineData[0]);
				std::vector<std::string> pilotData;
				while (std::getline(lineToParse, value, ','))
				{
					value = trim(value);
					pilotData.push_back(value);
				}

				this->config.pilots.push_back(pilotData);
			}
		}
	}
	else
	{
		std::cout << "Error: Could not read file " << path << std::endl;
		errorValue = 1;
	}

	return errorValue;
}

void Data::PrintConfig()
{
	std::cout << "DataPath: " << this->config.fileName << std::endl;

	std::cout << "Tax Rates: " << this->config.taxrate[0];
	for (int i = 1; i < 4; i++)
		std::cout << ", " << this->config.taxrate[i];
	std::cout << std::endl;

	std::cout << "Ore Reprocessing Rate: " << this->config.reprocess[0] << std::endl;

	std::cout << "Pilots:" << std::endl;
	for (int i = 0; i < this->config.pilots.size(); i++) 
	{
		std::cout << "\t" << this->config.pilots[i][0];
		for (int k = 1; k < this->config.pilots[i].size(); k++)
		{
			std::cout << ", " << this->config.pilots[i][k];
		}
		std::cout << std::endl;
	}

	
	std::cout << std::endl;
}

void Data::PrintOres()
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Ore Section: " << std::to_string(i+1) << std::endl;

		std::cout << "\t" << this->ore[i].type[0];
		for (int k = 1; k < 3; k++)
		{
			std::cout << ", " << this->ore[i].type[k];
		}
		std::cout << std::endl;

		std::cout << "\t" << this->ore[i].modifier[1];
		std::cout << ", " << this->ore[i].modifier[2] << std::endl;

		std::cout << "\t" << "Tax rate: " << this->ore[i].taxrate << std::endl;
		std::cout << std::endl;
	}
}

void Data::PrintRaw()
{
	for (int i = 0; i < this->raw.size(); i++)
	{
		for (int k = 0; k < 9; k++)
		{
			std::cout << this->raw[i][k] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}