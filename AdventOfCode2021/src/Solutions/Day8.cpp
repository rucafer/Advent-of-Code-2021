#include "Day8.h"

bool findSolution(char* solution, const std::vector<std::string>& patterns, int currentIndex);
bool checkSolution(char* solution, const std::vector<std::string>& patterns, int currentIndex);
int decode(const std::string& digit, char* solution);

std::string Day8::part1()
{
	auto input = loadFileAsStringList(pathToInput1);

	int result = 0;

	for (const auto& line : input)
	{
		std::string output = split(line, " | ")[1];
		auto digits = split(output, " ");
		for (const auto& digit : digits)
		{
			int size = digit.size();
			if (size == 2 || size == 4 || size == 3 || size == 7)
				result++;
		}
	}

	return std::to_string(result);
}

std::string Day8::part2()
{

	auto input = loadFileAsStringList(pathToInput1);

	int result = 0;

	for (const auto& line : input)
	{
		std::vector<std::string> patterns = split(split(line, " | ")[0], " ");
		std::vector<std::string> outputs = split(split(line, " | ")[1], " ");
		
		/* 
		Indices of the array:
			 0000
			1    2
			1    2
			 3333
			4    5
			4    5
			 6666
		*/

		char solution[7];
		memset(solution, 0, 7);
		findSolution(solution, patterns, 0);

		int number = 0;
		for (const auto& digit : outputs)
		{
			number *= 10;
			number += decode(digit, solution);
		}

		result += number;

	}

	return std::to_string(result);
}

bool findSolution(char* solution, const std::vector<std::string>& patterns, int currentIndex)
{
	if (currentIndex == 7)
		return true;

	for (char c = 'a'; c <= 'g'; c++)
	{
		solution[currentIndex] = c;

		if (checkSolution(solution, patterns, currentIndex))
		{
			if (findSolution(solution, patterns, currentIndex + 1))
			{
				return true;
			}
		}
	}

	return false;
}

bool checkSolution(char* solution, const std::vector<std::string>& patterns, int currentIndex)
{
	//Char already on the list
	for (int i = 0; i < currentIndex; i++)
	{
		if (solution[i] == solution[currentIndex])
		{
			return false;
		}
	}

	switch (currentIndex)
	{
	case 0:
		for (const auto& pattern : patterns)
		{
			//Found segment on a 1 or 4 --> incorrect
			if (pattern.size() == 2 || pattern.size() == 4)
			{
				if (pattern.find(solution[currentIndex]) != std::string::npos)
					return false;
			}
			//Segment not found on the other numbers --> incorrect
			else
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	case 1:
		for (const auto& pattern : patterns)
		{
			//Found segment on a 1 or 7 --> incorrect
			if (pattern.size() == 2 || pattern.size() == 3)
			{
				if (pattern.find(solution[currentIndex]) != std::string::npos)
					return false;
			}
			//Segment not found on 0 4 6 or 9  --> incorrect
			else if (pattern.size() == 6 || pattern.size() == 4)
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	case 2:
		for (const auto& pattern : patterns)
		{
			//Segment not found on 1 4 or 7  --> incorrect
			if (pattern.size() == 2 || pattern.size() == 4 || pattern.size() == 3)
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	case 3:
		for (const auto& pattern : patterns)
		{
			//Found segment on a 1 or 7 --> incorrect
			if (pattern.size() == 2 || pattern.size() == 3)
			{
				if (pattern.find(solution[currentIndex]) != std::string::npos)
					return false;
			}
			//Segment not found on 2 3 4 or 5  --> incorrect
			else if (pattern.size() == 5 || pattern.size() == 4)
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	case 4:
		for (const auto& pattern : patterns)
		{
			//Found segment on a 1 4 or 7 --> incorrect
			if (pattern.size() == 2 || pattern.size() == 3 || pattern.size() == 4)
			{
				if (pattern.find(solution[currentIndex]) != std::string::npos)
					return false;
			}
			
		}
		return true;

	case 5:
		for (const auto& pattern : patterns)
		{
			//Segment not found on 0 1 4 6 7 or 9  --> incorrect
			if (pattern.size() == 2 || pattern.size() == 3 || pattern.size() == 4 || pattern.size() == 6)
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	case 6:
		for (const auto& pattern : patterns)
		{
			//Found segment on a 1 4 or 7 --> incorrect
			if (pattern.size() == 2 || pattern.size() == 3 || pattern.size() == 4)
			{
				if (pattern.find(solution[currentIndex]) != std::string::npos)
					return false;
			}
			//Segment not found on other numbers --> incorrect
			else
			{
				if (pattern.find(solution[currentIndex]) == std::string::npos)
					return false;
			}
		}
		return true;

	default:
		return false;
	}
}

int decode(const std::string& digit, char* solution)
{
	if (digit.size() == 2)
		return 1;
	else if (digit.size() == 3)
		return 7;
	else if (digit.size() == 4)
		return 4;
	else if (digit.size() == 7)
		return 8;
	else if (digit.size() == 5)
	{
		if (digit.find(solution[1]) != std::string::npos)
			return 5;
		else if (digit.find(solution[4]) != std::string::npos)
			return 2;
		else
			return 3;
	}
	else
	{
		if (digit.find(solution[3]) == std::string::npos)
			return 0;
		else if (digit.find(solution[4]) != std::string::npos)
			return 6;
		else
			return 9;
	}
}