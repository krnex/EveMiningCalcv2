#include"Help.h"

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

std::vector<std::string> splitOreName(std::string string, char delim)
{
	std::vector<std::string> splitStrings;

	if (std::count(string.begin(), string.end(), delim) == 0)
		splitStrings.push_back("");

	size_t pos = 0;
	while ((pos = string.find(delim)) != std::string::npos)
	{
		splitStrings.push_back(string.substr(0, pos));
		string.erase(0, pos + 1);
	}
	splitStrings.push_back(string);


	return splitStrings;
}

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	localtime_s(&tstruct, &now);
	char       buf[80];
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	return buf;
}