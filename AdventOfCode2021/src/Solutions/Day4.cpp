#include "Day4.h"

class Board
{
public:
	Board(const std::vector<std::string>& numbersStr)
	{
		for (int i = 0; i < 5; i++)
		{
			auto strs = split(numbersStr[i], " ");
			for (int j = 0; j < 5; j++)
			{
				numbers[i][j] = std::atoi(strs[j].c_str());
				marked[i][j] = false;
			}
		}
	}

	int addNumber(int number)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (numbers[i][j] == number)
				{
					marked[i][j] = true;

					if (isWinner(i, j))
					{
						return getUnmarkedSum() * number;
					}
				}
			}
		}

		return -1;
	}

private:

	bool isWinner(int row, int col)
	{
		//Check row
		bool winner = true;
		for (int i = 0; i < 5; i++)
		{
			if (marked[row][i] == false)
			{
				winner = false;
				break;
			}
		}

		if (winner) return true;

		winner = true;
		for (int i = 0; i < 5; i++)
		{
			if (marked[i][col] == false)
			{
				return false;
			}
		}

		return true;
	}

	int getUnmarkedSum()
	{
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (!marked[i][j])
					sum += numbers[i][j];
			}
		}

		return sum;
	}

private:
	int numbers[5][5];
	bool marked[5][5];
};

std::string Day4::part1()
{
	auto input = loadFileAsStringList(pathToInput1);

	std::vector<int> numbers;

	for (const auto& str : split(input[0], ","))
	{
		numbers.push_back(std::atoi(str.c_str()));
	}

	std::vector<Board> boards;

	int fileLine = 1;
	while (fileLine < input.size())
	{
		std::vector<std::string> boardStrs;
		for (int i = fileLine + 1; i < fileLine + 1 + 5; i++)
		{
			boardStrs.push_back(input[i]);
		}

		boards.emplace_back(boardStrs);

		//Board + blank line
		fileLine += 6;
	}



	for (int number : numbers)
	{
		for (Board& board : boards)
		{
			int score = board.addNumber(number);
			if (score != -1)
			{
				return std::to_string(score);
			}
			
		}
	}

	return "Solution not found";
}

std::string Day4::part2()
{
	auto input = loadFileAsStringList(pathToInput1);

	std::vector<int> numbers;

	for (const auto& str : split(input[0], ","))
	{
		numbers.push_back(std::atoi(str.c_str()));
	}

	std::vector<Board> boards;

	int fileLine = 1;
	while (fileLine < input.size())
	{
		std::vector<std::string> boardStrs;
		for (int i = fileLine + 1; i < fileLine + 1 + 5; i++)
		{
			boardStrs.push_back(input[i]);
		}

		boards.emplace_back(boardStrs);

		//Board + blank line
		fileLine += 6;
	}



	for (int number : numbers)
	{


		auto it = boards.begin();
		while(it != boards.end())
		{
			int score = (*it).addNumber(number);
			if (score != -1)
			{
				if (boards.size() == 1)
				{
					return std::to_string(score);
				}
				
				it = boards.erase(it);
			}
			else
				it++;
		}
	}

	return "Solution not found";
}