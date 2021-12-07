#include "Day2.h"

std::string Day2::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int pos = 0, depth = 0;

	for (const auto& command : input)
	{
		auto strs = split(command, " ");

		int number = std::stoi(strs[1]);

		if (strs[0] == "forward")
			pos += number;
		else if (strs[0] == "down")
			depth += number;
		else if (strs[0] == "up")
			depth -= number;
		else return "Error";
	}

	
	return std::to_string(depth * pos);
}

std::string Day2::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int pos = 0, depth = 0, aim = 0;

	for (const auto& command : input)
	{
		auto strs = split(command, " ");

		int number = std::stoi(strs[1]);

		if (strs[0] == "forward")
		{
			pos += number;
			depth += aim * number;
		}
		else if (strs[0] == "down")
			aim += number;
		else if (strs[0] == "up")
			aim -= number;
		else return "Error";
	}


	return std::to_string(depth * pos);
}