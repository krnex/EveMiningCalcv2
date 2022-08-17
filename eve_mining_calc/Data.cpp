#include "Data.h"

Data::Data(std::string path)
{
	this->OpenConfigFile(path);
	this->OpenRawFile(this->config.fileName);

	OreSection section1 = { 
		{"Bitumens", "Coesite", "Sylvite", "Zeolites"},

		{std::vector<std::string>{"Hydrocarbons",      "Pye", "Mex"}, 
		 std::vector<std::string>{"Silicates",         "Pye", "Mex"},
		 std::vector<std::string>{"Evaporite Deposits","Pye", "Mex"},
		 std::vector<std::string>{"Atmospheric Gases", "Pye", "Mex"}
		},

		{65, 2000, 400},
		{3,1,2,4},

		{"", "Brimful", "Glistening"},
		this->config.taxrate[0]
	};

	OreSection section2 = { 
		{"Cobalitite", "Euxenite", "Scheelite", "Titanite"},

		{std::vector<std::string>{"Cobalt"},
		 std::vector<std::string>{"Scandium"},
		 std::vector<std::string>{"Tungsten"},
		 std::vector<std::string>{"Titanium"}
		},
		{40},
		{1,1,1,1},

		{"", "Copious", "Twinkling" },
		this->config.taxrate[1]
	};

	OreSection section3 = { 
		{"Chromite", "Otavite", "Sperrylite", "Vanadinite"},

		{std::vector<std::string>{"Hydrocarbons",       "Chromium"},
		 std::vector<std::string>{"Atmospheric Gases",  "Cadmium"},
		 std::vector<std::string>{"Evaporite Deposits", "Platinum"},
		 std::vector<std::string>{"Silicates",          "Vanadium"}
		},
		{10, 40},
	    {1,1,1,1},

		{"", "Lavish", "Shimmering"},
		this->config.taxrate[2]
	};

	OreSection section4 = {
		{"Carnotite", "Cinnabar", "Pollucite", "Zircon"},

		{std::vector<std::string>{"Atmospheric Gases",  "Cobalt",   "Technetium"},
		 std::vector<std::string>{"Evaporite Deposits", "Tungsten", "Mercury"},
		 std::vector<std::string>{"Hydrocarbons",       "Scandium", "Caesium"},
		 std::vector<std::string>{"Silicates",          "Titanium", "Hafnium"}
		},
		{15, 10, 50},
		{1,1,1,1},

		{"", "Replete", "Glowing"},
		this->config.taxrate[3]
	};

	OreSection section5 = {
		{"Loparite", "Monazite", "Xenotime", "Ytterbite"},

		{std::vector<std::string>{"Hydrocarbons",       "Scandium",   "Platinum", "Promethium"},
		 std::vector<std::string>{"Evaporite Deposits", "Tungsten",   "Chromium", "Neodymium"},
		 std::vector<std::string>{"Atmospheric Gases",  "Cobalt",     "Vanadium", "Dysprosium"},
		 std::vector<std::string>{"Silicates",          "Titanium",   "Cadmium",  "Thulium"}
		},
		{20, 20, 10 ,22},
		{1,1,1,1},

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
		std::cerr << "Error: Could not read file " << path << std::endl;
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
		std::cerr << "Error: Could not read file " << path << std::endl;
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
		std::cout << "Ore Section " << std::to_string(i+1) << ":" << std::endl;

		std::cout << "\t" << this->ore[i].modifier[1];
		std::cout << ", " << this->ore[i].modifier[2] << std::endl;

		std::cout << "\t" << "Tax rate: " << this->ore[i].taxrate << std::endl;

		for (int k = 0; k < 4; k++)
		{
			std::cout << "\t" << this->ore[i].type[k] << ":\n";

			for (int l = 0; l < this->ore[i].refinedTypes[k].size(); l++)
			{
				std::cout << "\t\t" << (this->ore[i].refinedTypes[k][l] == "Pye" ? this->ore[i].refinedValues[l] * this->ore[i].pyeModifer[k] : this->ore[i].refinedValues[l]) << " " << this->ore[i].refinedTypes[k][l] << std::endl;
			}
		}

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