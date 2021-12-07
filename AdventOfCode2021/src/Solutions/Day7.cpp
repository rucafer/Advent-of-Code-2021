#include "Day7.h"
#include <algorithm>


std::string Day7::part1()
{
	std::vector<int> input = loadFileAsIntListComma(pathToInput1);

	int min = *std::min_element(input.begin(), input.end());
	int max = *std::max_element(input.begin(), input.end());

	int minFuel = INT_MAX;

	for (int i = min; i <= max; i++)
	{
		int fuel = 0;
		for (int number : input)
		{
			fuel += std::abs(number - i);
		}

		if (fuel < minFuel)
			minFuel = fuel;
	}

	return std::to_string(minFuel);
}

std::string Day7::part2()
{
	std::vector<int> input = loadFileAsIntListComma(pathToInput1);

	int min = *std::min_element(input.begin(), input.end());
	int max = *std::max_element(input.begin(), input.end());

	//Calculate all sums and cache them
	std::vector<int>sums;
	int accumulator = 0;
	for (int i = 0; i < max - min + 1; i++)
	{
		accumulator += i;
		sums.push_back(accumulator);
	}

	int minFuel = INT_MAX;

	for (int i = min; i <= max; i++)
	{
		int fuel = 0;
		for (int number : input)
		{
			int steps = std::abs(number - i);
			fuel += sums[steps];
		}

		if (fuel < minFuel)
			minFuel = fuel;
	}

	return std::to_string(minFuel);
}