#include "Day14.h"

#include <unordered_map>
#include <string>

#define STEPS 10
#define STEPS2 40

long long getResult(const std::string& inputPath, int steps);

std::string Day14::part1()
{
	return std::to_string(getResult(pathToInput1, STEPS));
}

std::string Day14::part2()
{
	return std::to_string(getResult(pathToInput1, STEPS2));
}

long long getResult(const std::string& inputPath, int steps)
{
	std::vector<std::string> input = loadFileAsStringList(inputPath);

	std::string templ = input[0];

	std::unordered_map<std::string, char> rules;
	std::unordered_map<std::string, long long> pairCount;


	for (size_t i = 2; i < input.size(); i++)
	{
		std::string head = split(input[i], " -> ")[0];
		char tail = split(input[i], " -> ")[1][0];
		rules[head] = tail;
	}

	for (size_t i = 0; i < templ.size() - 1; i++)
	{
		std::string head;
		head += templ[i];
		head += templ[i + 1];
		pairCount[head]++;
	}

	for (int step = 0; step < steps; step++)
	{
		std::unordered_map<std::string, long long> newPairCount;
		for (const auto& pair : pairCount)
		{
			long long count = pair.second;
			std::string pair1;
			std::string pair2;
			pair1 += pair.first[0];
			pair1 += rules[pair.first];
			pair2 += rules[pair.first];
			pair2 += pair.first[1];

			newPairCount[pair1] += count;
			newPairCount[pair2] += count;
		}

		pairCount = newPairCount;
	}

	std::unordered_map<char, long long> count1;
	//Count for the second character of the pair
	//This is done so that characters which are in a pair (except the first and the last) aren't counted twice
	std::unordered_map<char, long long> count2;
	std::unordered_map<char, long long> finalCount;

	for (const auto& pair : pairCount)
	{
		count1[pair.first[0]] += pair.second;
		count2[pair.first[1]] += pair.second;
	}

	long long min = LLONG_MAX, max = 0;

	//The correct value is the bigger between count1 and count2 (this ensures that the first and the last characters of the string are counted)
	for (const auto& pair : count1)
	{
		if (pair.second > count2[pair.first])
			finalCount[pair.first] = pair.second;
		else
			finalCount[pair.first] = count2[pair.first];
	}

	for (const auto& pair : finalCount)
	{
		if (pair.second > max)
			max = pair.second;
		if (pair.second < min)
			min = pair.second;
	}

	return max - min;
}