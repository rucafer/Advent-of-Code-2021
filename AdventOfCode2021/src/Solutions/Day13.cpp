#include "Day13.h"

#define MAXROWSIZE 10000

std::string Day13::part1()
{
	int result = 0;

	std::vector<int> points;

	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	size_t curLine = 0;

	for (curLine = 0; curLine < input.size(); curLine++)
	{
		std::string& line = input[curLine];

		if (line.empty())
			break;

		int row, col;
		row = std::atoi(split(line, ",")[1].c_str());
		col = std::atoi(split(line, ",")[0].c_str());

		points.push_back(row * MAXROWSIZE + col);
	}
	curLine++;

	bool foldOnX = input[curLine][11] == 'x';
	int foldLine = std::atoi(input[curLine].substr(13, input[curLine].size() - 13).c_str());

	//Fold on X
	if (foldOnX)
	{
		std::vector<int> newPointList;
		for (int point : points)
		{
			int col = point % MAXROWSIZE;
			int row = point / MAXROWSIZE;
			if (col > foldLine)
			{
				int newCol = foldLine * 2 - col;
				if (std::find(points.begin(), points.end(), row * MAXROWSIZE + newCol) == points.end())
				{
					newPointList.push_back(row * MAXROWSIZE + newCol);
				}
			}
			else
			{
				newPointList.push_back(point);
			}
		}

		result = newPointList.size();
	}
	else
	{
		std::vector<int> newPointList;
		for (int point : points)
		{
			int col = point % MAXROWSIZE;
			int row = point / MAXROWSIZE;
			if (row > foldLine)
			{
				int newRow = foldLine * 2 - row;
				if (std::find(points.begin(), points.end(), newRow * MAXROWSIZE + col) == points.end())
				{
					newPointList.push_back(newRow * MAXROWSIZE + col);
				}
			}
			else
			{
				newPointList.push_back(point);
			}
		}

		result = newPointList.size();
	}

	return std::to_string(result);
}

std::string Day13::part2()
{
	std::vector<int> points;

	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	size_t curLine = 0;

	for (curLine = 0; curLine < input.size(); curLine++)
	{
		std::string& line = input[curLine];

		if (line.empty())
			break;

		int row, col;
		row = std::atoi(split(line, ",")[1].c_str());
		col = std::atoi(split(line, ",")[0].c_str());

		points.push_back(row * MAXROWSIZE + col);
	}
	curLine++;

	while (curLine < input.size())
	{
		bool foldOnX = input[curLine][11] == 'x';
		int foldLine = std::atoi(input[curLine].substr(13, input[curLine].size() - 13).c_str());

		//Fold on X
		if (foldOnX)
		{
			std::vector<int> newPointList;
			for (int point : points)
			{
				int col = point % MAXROWSIZE;
				int row = point / MAXROWSIZE;
				if (col > foldLine)
				{
					int newCol = foldLine * 2 - col;
					if (std::find(points.begin(), points.end(), row * MAXROWSIZE + newCol) == points.end())
					{
						newPointList.push_back(row * MAXROWSIZE + newCol);
					}
				}
				else
				{
					newPointList.push_back(point);
				}
			}

			points = newPointList;
		}
		else
		{
			std::vector<int> newPointList;
			for (int point : points)
			{
				int col = point % MAXROWSIZE;
				int row = point / MAXROWSIZE;
				if (row > foldLine)
				{
					int newRow = foldLine * 2 - row;
					if (std::find(points.begin(), points.end(), newRow * MAXROWSIZE + col) == points.end())
					{
						newPointList.push_back(newRow * MAXROWSIZE + col);
					}
				}
				else
				{
					newPointList.push_back(point);
				}
			}

			points = newPointList;
		}

		curLine++;
	}

	int numRows = 0, numCols = 0;
	for (int point : points)
	{
		int row = point / MAXROWSIZE;
		int col = point % MAXROWSIZE;
		if (row > numRows)
			numRows = row;
		if (col > numCols)
			numCols = col;
	}
	numRows += 1;
	//Space for linebreak
	numCols += 2;

	char* result = new char[numRows * numCols];

	memset(result, '.', numRows * numCols);


	for (int i = 0; i < numRows; i++)
	{
		result[i * numCols + numCols - 1] = '\n';
	}

	result[numRows * numCols - 1] = 0;


	for (int point : points)
	{
		int row = point / MAXROWSIZE;
		int col = point % MAXROWSIZE;

		result[row * numCols + col] = '#';
	}

	std::string resultStr(result);
	resultStr = "\n" + resultStr + "\n";

	delete[] result;

	return resultStr;
}