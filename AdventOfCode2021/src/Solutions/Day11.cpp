#include "Day11.h"

#define GRIDSIZE 10

#define getValue(x, y) input[(x) * GRIDSIZE + (y)]

std::string Day11::part1()
{
	int result = 0;

	std::vector<std::string> inputStr = loadFileAsStringList(pathToInput1);

	char* input = new char[GRIDSIZE * GRIDSIZE];

	for (int row = 0; row < GRIDSIZE; row++)
	{
		for (int col = 0; col < GRIDSIZE; col++)
		{
			getValue(row, col) = inputStr[row][col] - '0';
		}
	}

	int step = 0;

	while (step < 100)
	{
		std::vector<std::pair<int, int>> flashes;

		//Increase energy level
		for (int row = 0; row < GRIDSIZE; row++)
		{
			for (int col = 0; col < GRIDSIZE; col++)
			{
				getValue(row, col)++;
				if (getValue(row, col) > 9)
				{
					flashes.emplace_back(row, col);
				}
			}
		}

		for (size_t i = 0; i < flashes.size(); i++)
		{
			int row = flashes[i].first, col = flashes[i].second;

			if (row > 0)
			{
				//Top left
				if (col > 0)
				{
					getValue(row - 1, col - 1)++;
					if (getValue(row - 1, col - 1) == 10)
						flashes.emplace_back(row - 1, col - 1);
				}

				//Top
				getValue(row - 1, col)++;
				if (getValue(row - 1, col) == 10)
					flashes.emplace_back(row - 1, col);

				//Top right
				if (col < GRIDSIZE - 1)
				{
					getValue(row - 1, col + 1)++;
					if (getValue(row - 1, col + 1) == 10)
						flashes.emplace_back(row - 1, col + 1);
				}
			}

			//Left
			if (col > 0)
			{
				getValue(row, col - 1)++;
				if (getValue(row, col - 1) == 10)
					flashes.emplace_back(row, col - 1);
			}

			//Right
			if (col < GRIDSIZE - 1)
			{
				getValue(row, col + 1)++;
				if (getValue(row, col + 1) == 10)
					flashes.emplace_back(row, col + 1);
			}


			if (row < GRIDSIZE - 1)
			{
				//Bottom left
				if (col > 0)
				{
					getValue(row + 1, col - 1)++;
					if (getValue(row + 1, col - 1) == 10)
						flashes.emplace_back(row + 1, col - 1);
				}

				//Bottom
				getValue(row + 1, col)++;
				if (getValue(row + 1, col) == 10)
					flashes.emplace_back(row + 1, col);

				//Bottom right
				if (col < GRIDSIZE - 1)
				{
					getValue(row + 1, col + 1)++;
					if (getValue(row + 1, col + 1) == 10)
						flashes.emplace_back(row + 1, col + 1);
				}
			}
		}

		for (const auto& flash : flashes)
		{
			getValue(flash.first, flash.second) = 0;
		}

		result += flashes.size();
		step++;
	}

	return std::to_string(result);
}

std::string Day11::part2()
{
	std::vector<std::string> inputStr = loadFileAsStringList(pathToInput1);

	char* input = new char[GRIDSIZE * GRIDSIZE];

	for (int row = 0; row < GRIDSIZE; row++)
	{
		for (int col = 0; col < GRIDSIZE; col++)
		{
			getValue(row, col) = inputStr[row][col] - '0';
		}
	}

	int step = 0;

	while (true)
	{
		std::vector<std::pair<int, int>> flashes;

		//Increase energy level
		for (int row = 0; row < GRIDSIZE; row++)
		{
			for (int col = 0; col < GRIDSIZE; col++)
			{
				getValue(row, col)++;
				if (getValue(row, col) > 9)
				{
					flashes.emplace_back(row, col);
				}
			}
		}

		for (size_t i = 0; i < flashes.size(); i++)
		{
			int row = flashes[i].first, col = flashes[i].second;

			if (row > 0)
			{
				//Top left
				if (col > 0)
				{
					getValue(row - 1, col - 1)++;
					if (getValue(row - 1, col - 1) == 10)
						flashes.emplace_back(row - 1, col - 1);
				}

				//Top
				getValue(row - 1, col)++;
				if (getValue(row - 1, col) == 10)
					flashes.emplace_back(row - 1, col);

				//Top right
				if (col < GRIDSIZE - 1)
				{
					getValue(row - 1, col + 1)++;
					if (getValue(row - 1, col + 1) == 10)
						flashes.emplace_back(row - 1, col + 1);
				}
			}

			//Left
			if (col > 0)
			{
				getValue(row, col - 1)++;
				if (getValue(row, col - 1) == 10)
					flashes.emplace_back(row, col - 1);
			}

			//Right
			if (col < GRIDSIZE - 1)
			{
				getValue(row, col + 1)++;
				if (getValue(row, col + 1) == 10)
					flashes.emplace_back(row, col + 1);
			}


			if (row < GRIDSIZE - 1)
			{
				//Bottom left
				if (col > 0)
				{
					getValue(row + 1, col - 1)++;
					if (getValue(row + 1, col - 1) == 10)
						flashes.emplace_back(row + 1, col - 1);
				}

				//Bottom
				getValue(row + 1, col)++;
				if (getValue(row + 1, col) == 10)
					flashes.emplace_back(row + 1, col);

				//Bottom right
				if (col < GRIDSIZE - 1)
				{
					getValue(row + 1, col + 1)++;
					if (getValue(row + 1, col + 1) == 10)
						flashes.emplace_back(row + 1, col + 1);
				}
			}
		}

		for (const auto& flash : flashes)
		{
			getValue(flash.first, flash.second) = 0;
		}

		if (flashes.size() == GRIDSIZE * GRIDSIZE)
			return std::to_string(step + 1);

		step++;
	}

	return "Result not found";
}