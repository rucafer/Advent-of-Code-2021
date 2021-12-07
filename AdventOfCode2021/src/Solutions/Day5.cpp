#include "Day5.h"


#define SIZE 1000

#define getPoint(x, y) points[(x) * SIZE + (y)]

std::string Day5::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int* points = (int*)malloc(SIZE * SIZE * sizeof(int));

	if (points == nullptr)
		return "Error";
	memset(points, 0, SIZE * SIZE * sizeof(int));

	for (const auto& line : input)
	{
		int x1, x2;
		int y1, y2;

		std::vector<std::string> strs = split(line, " -> ");

		x1 = std::atoi(split(strs[0], ",")[0].c_str());
		y1 = std::atoi(split(strs[0], ",")[1].c_str());

		x2 = std::atoi(split(strs[1], ",")[0].c_str());
		y2 = std::atoi(split(strs[1], ",")[1].c_str());

		if (x1 >= SIZE || y1 >= SIZE || x2 >= SIZE || y2 >= SIZE)
			return "Points array is to small";

		if (x1 == x2)
		{
			for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++)
			{
				getPoint(x1, i)++;
			}
		}
		else if (y1 == y2)
		{
			for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++)
			{
				getPoint(i, y1)++;
			}
		}

	}
	
	int result = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (getPoint(i, j) >= 2)
				result++;
		}
	}
	
	return std::to_string(result);
}

std::string Day5::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int* points = (int*)malloc(SIZE * SIZE * sizeof(int));

	if (points == nullptr)
		return "Error";
	memset(points, 0, SIZE * SIZE * sizeof(int));

	for (const auto& line : input)
	{
		int x1, x2;
		int y1, y2;

		std::vector<std::string> strs = split(line, " -> ");

		x1 = std::atoi(split(strs[0], ",")[0].c_str());
		y1 = std::atoi(split(strs[0], ",")[1].c_str());

		x2 = std::atoi(split(strs[1], ",")[0].c_str());
		y2 = std::atoi(split(strs[1], ",")[1].c_str());

		if (x1 >= SIZE || y1 >= SIZE || x2 >= SIZE || y2 >= SIZE)
			return "Points array is to small";

		if (x1 == x2)
		{
			for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++)
			{
				getPoint(x1, i)++;
			}
		}
		else if (y1 == y2)
		{
			for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++)
			{
				getPoint(i, y1)++;
			}
		}
		else
		{
			for (int i = 0; i <= std::abs(x1 - x2); i++)
			{
				if (x2 > x1)
				{
					if (y2 > y1)
						getPoint(x1 + i, y1 + i)++;
					else
						getPoint(x1 + i, y1 - i)++;
				}
				else
				{
					if (y2 > y1)
						getPoint(x1 - i, y1 + i)++;
					else
						getPoint(x1 - i, y1 - i)++;
				}
			}
		}
	}

	int result = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (getPoint(i, j) >= 2)
				result++;
		}
	}

	return std::to_string(result);
}