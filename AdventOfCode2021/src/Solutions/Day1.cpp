#include "Day1.h"

std::string Day1::part1()
{
	std::vector<int> input= loadFileAsIntList(pathToInput1);

	int result = 0;

	for (int i = 1; i < input.size(); i++)
	{
		if (input[i] > input[i - 1])
			result++;
	}

	return std::to_string(result);
}

std::string Day1::part2()
{
	std::vector<int> input = loadFileAsIntList(pathToInput1);

	int result = 0;

	for (int i = 1; i < input.size() - 2; i++)
	{
		int sum1 = input[i - 1] + input[i] + input[i + 1];
		int sum2 = input[i] + input[i + 1] + input[i + 2];

		if (sum2 > sum1)
			result++;
	}

	return std::to_string(result);
}