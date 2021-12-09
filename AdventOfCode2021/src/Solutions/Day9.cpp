#include "Day9.h"

#include <algorithm>

#define getValue(x, y) heightmap[(x) * cols + (y)]
#define getValueVisited(x, y) visited[(x) * cols + (y)]

void getBasin(int i, int j, char* heightmap, bool* visited, int rows, int cols, int* result);

std::string Day9::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);
	size_t rows = input.size();
	size_t cols = input[0].size();

	char* heightmap = new char[rows * cols];

	int result = 0;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			getValue(i, j) = (char)(input[i][j] - '0');
		}
	}

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			//up
			if (i > 0 && getValue(i - 1, j) <= getValue(i, j))
				continue;
			//down
			if (i < rows - 1 && getValue(i + 1, j) <= getValue(i, j))
				continue;
			//left
			if (j > 0 && getValue(i, j - 1) <= getValue(i, j))
				continue;
			//right
			if (j < cols - 1 && getValue(i, j + 1) <= getValue(i, j))
				continue;

			result += (1 + getValue(i, j));
		}
	}

	delete[] heightmap;

	return std::to_string(result);
}

std::string Day9::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);
	size_t rows = input.size();
	size_t cols = input[0].size();

	char* heightmap = new char[rows * cols];
	bool* visited = new bool[rows * cols];
	std::vector<int> sizes;

	memset(visited, 0, rows * cols * sizeof(bool));

	std::vector<std::pair<size_t, size_t>> lowPoints;

	int result = 1;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			getValue(i, j) = (char)(input[i][j] - '0');
		}
	}

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			//up
			if (i > 0 && getValue(i - 1, j) <= getValue(i, j))
				continue;
			//down
			if (i < rows - 1 && getValue(i + 1, j) <= getValue(i, j))
				continue;
			//left
			if (j > 0 && getValue(i, j - 1) <= getValue(i, j))
				continue;
			//right
			if (j < cols - 1 && getValue(i, j + 1) <= getValue(i, j))
				continue;

			lowPoints.emplace_back(i, j);
		}
	}

	for (const auto& lowPoint : lowPoints)
	{
		int size = 0;
		getBasin(lowPoint.first, lowPoint.second, heightmap, visited, rows, cols, &size);
		sizes.push_back(size);
	}

	std::sort(sizes.begin(), sizes.end(), std::greater<int>());

	result *= sizes[0] * sizes[1] * sizes[2];

	delete[] heightmap;
	delete[] visited;

	return std::to_string(result);
}

void getBasin(int i, int j, char* heightmap, bool* visited, int rows, int cols, int* result)
{
	(*result)++;

	//up
	if (i > 0 && !getValueVisited(i - 1, j) && getValue(i - 1, j) != 9 && getValue(i - 1, j) > getValue(i, j))
	{
		getBasin(i - 1, j, heightmap, visited, rows, cols, result);
		getValueVisited(i - 1, j) = true;
	}
	//down
	if (i < rows - 1 && !getValueVisited(i + 1, j) && getValue(i + 1, j) != 9 && getValue(i + 1, j) > getValue(i, j))
	{
		getBasin(i + 1, j, heightmap, visited, rows, cols, result);
		getValueVisited(i + 1, j) = true;
	}
	//left
	if (j > 0 && !getValueVisited(i, j - 1) && getValue(i, j - 1) != 9 && getValue(i, j - 1) > getValue(i, j))
	{
		getBasin(i, j - 1, heightmap, visited, rows, cols, result);
		getValueVisited(i, j - 1) = true;
	}
	//right
	if (j < cols - 1 && !getValueVisited(i, j + 1) && getValue(i, j + 1) != 9 && getValue(i, j + 1) > getValue(i, j))
	{
		getBasin(i, j + 1, heightmap, visited, rows, cols, result);
		getValueVisited(i, j + 1) = true;
	}
}
