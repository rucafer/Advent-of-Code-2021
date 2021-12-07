#include "Day6.h"

#define DAYS 80
#define DAYS2 256

long long getNumberOfChildren(int intialState, int days)
{
	std::vector<int> fishes;
	fishes.push_back(intialState);
	for (int i = 0; i < days; i++)
	{
		size_t iterations = fishes.size();
		for (size_t j = 0; j < iterations; j++)
		{
			fishes[j]--;
			if (fishes[j] == -1)
			{
				fishes[j] = 6;
				fishes.push_back(8);
			}
		}
	}

	return fishes.size();
}


//Brute force method (caching results for better speeed)
std::string Day6::part1()
{
	std::vector<int> input = loadFileAsIntListComma(pathToInput1);
	
	long long calculatedResults[10];

	for (int i = 0; i <= 9; i++)
	{
		calculatedResults[i] = getNumberOfChildren(i, DAYS);
	}
	
	long long result = 0;
	for (int i : input)
	{
		result += calculatedResults[i];
	}
	return std::to_string(result);
}

//Better algorithm
std::string Day6::part2()
{
	std::vector<int> input = loadFileAsIntListComma(pathToInput1);

	long long fishsesInState[9];

	for (int i = 0; i < 9; i++)
	{
		fishsesInState[i] = 0;
	}

	for (int i : input)
	{
		fishsesInState[i]++;
	}

	for (int iteration = 0; iteration < DAYS2; iteration++)
	{
		long long fishesAt0 = fishsesInState[0];
	
		//Decrease current cycle
		for (int i = 1; i < 9; i++)
		{
			fishsesInState[i - 1] = fishsesInState[i];
		}

		//Rest cycles
		fishsesInState[6] += fishesAt0;
		//Spawn new fishes
		fishsesInState[8] = fishesAt0;
	}

	long long result = 0;
	for (int i = 0; i < 9; i++)
	{
		result += fishsesInState[i];
	}

	return std::to_string(result);
}