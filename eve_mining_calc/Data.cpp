#include "Data.h"

Data::Data()
{
	
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

}

