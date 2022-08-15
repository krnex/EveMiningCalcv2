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