#include "Utils.h"

#include <string>

//GLOBAL CONSTANTS AND PROGRAM SETTINGS
bool writeDebuggingInfo = false;

std::string getDayHeader(int dayNumber)
{
	std::string result = "\n\x1B[33m******************************\n*********** DAY ";
	if (dayNumber < 10)
	{
		result += " ";
	}
	result += std::to_string(dayNumber);
	
	result += " ***********\n******************************\033[0m\n";
	return result;
}



std::vector<int> loadFileAsIntList(const std::string& file)
{
	std::vector<int> result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			std::vector<std::string> splitResult = split(line, " ");
			for (std::string number : splitResult)
			{
				result.push_back(std::stoi(number));
			}
		}
	}
	return result;
}

std::vector<int> loadFileAsIntListComma(const std::string& file)
{
	std::vector<int> result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			std::vector<std::string> splitResult = split(line, ",");
			for (std::string number : splitResult)
			{
				result.push_back(std::stoi(number));
			}
		}
	}
	return result;
}

std::vector<long long> loadFileAsLongList(const std::string& file)
{
	std::vector<long long> result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			std::vector<std::string> splitResult = split(line, " ");
			for (std::string number : splitResult)
			{
				result.push_back(std::stoll(number));
			}
		}
	}
	return result;
}

std::vector<std::string> loadFileAsStringList(const std::string& file)
{
	std::vector<std::string> result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			result.push_back(line);
		}
	}
	return result;
}


std::string loadFileAsString(const std::string& file)
{
	std::string result;

	std::ifstream ifs(file);
	if (ifs)
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			result += line + '\n';
		}
	}
	return result;
}

std::vector<std::string> split(const std::string& input, const std::string& token)
{
	std::vector<std::string> result;
	
	bool hasFinished = false;

	size_t substrStart = 0 , substrEnd = 0;

	while (!hasFinished)
	{
		substrEnd = input.find(token, substrStart);

		if (substrEnd == std::string::npos)
		{
			hasFinished = true;
			substrEnd = input.size();
		}

		std::string substr = input.substr(substrStart, substrEnd - substrStart);
		if (substr.size() != 0)
		{
			result.push_back(substr);
		}

		substrStart = substrEnd + token.size();;
	}

	return result;
}