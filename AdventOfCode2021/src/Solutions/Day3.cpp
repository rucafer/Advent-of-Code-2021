#include "Day3.h"


std::string Day3::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::vector<std::vector<char>> bits;

	int i = 0;
	for (const auto& line : input)
	{
		bits.emplace_back();

		std::vector<char>& bitsLine = bits[bits.size() - 1];

		for (char c : line)
		{
			bitsLine.push_back(c);
		}
	}

	int gamma = 0;

	for (size_t i = 0; i < bits[0].size(); i++)
	{
		int count0 = 0, count1 = 0;

		for (size_t j = 0; j < bits.size(); j++)
		{
			if (bits[j][i] == '1')
				count1++;
			else
				count0++;
		}

		gamma *= 2;

		if (count1 > count0)
			gamma += 1;
	}

	//Epsilon can be calculated as the maximum binary number - gamma (bitwise inverse)
	int epsilon = (int) pow(2, bits[0].size()) - 1 - gamma;

	return std::to_string(gamma * epsilon);
}

std::string Day3::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::vector<std::vector<char>> bits;

	int i = 0;
	for (const auto& line : input)
	{
		bits.emplace_back();

		std::vector<char>& bitsLine = bits[bits.size() - 1];

		for (char c : line)
		{
			bitsLine.push_back(c);
		}
	}

	std::vector<std::vector<char>> o2List = bits;

	int iteration = 0;
	while (o2List.size() > 1)
	{
		int count0 = 0, count1 = 0;

		for (size_t j = 0; j < o2List.size(); j++)
		{
			if (o2List[j][iteration] == '1')
				count1++;
			else
				count0++;
		}

		auto it = o2List.begin();
		while (it != o2List.end())
		{
			bool erase = false;
			if ((*it)[iteration] == '1')
			{
				erase = count1 < count0;
			}
			else
			{
				erase = count1 >= count0;
			}

			if (erase)
				it = o2List.erase(it);
			else
				it++;
		}

		iteration++;
	}

	std::vector<std::vector<char>> co2List = bits;
	iteration = 0;

	while (co2List.size() > 1)
	{
		int count0 = 0, count1 = 0;

		for (size_t j = 0; j < co2List.size(); j++)
		{
			if (co2List[j][iteration] == '1')
				count1++;
			else
				count0++;
		}

		auto it = co2List.begin();
		while (it != co2List.end())
		{
			bool erase = false;
			if ((*it)[iteration] == '1')
			{
				erase = count1 >= count0;
			}
			else
			{
				erase = count1 < count0;
			}

			if (erase)
				it = co2List.erase(it);
			else
				it++;
		}

		iteration++;
	}

	int o2 = 0, co2 = 0;

	//convert to binary
	for (char c : o2List[0])
	{
		o2 *= 2;
		if (c == '1')
			o2++;
	}
	for (char c : co2List[0])
	{
		co2 *= 2;
		if (c == '1')
			co2++;
	}


	return std::to_string(co2 * o2);
}