#include "Day10.h"
#include <stack>
#include <algorithm>


std::string Day10::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int result = 0;

	for (const auto& line : input)
	{
		std::stack<char> chars;
		bool errorFound = false;
		for (char c : line)
		{
			if (c == '(' || c == '[' || c == '{' || c == '<')
			{
				chars.push(c);
			}
			else
			{
				char c2 = chars.top();
				chars.pop();

				switch (c)
				{
				case ')':
					if (c2 != '(')
					{
						errorFound = true;
						result += 3;
					}	
					break;
				case ']':
					if (c2 != '[')
					{
						errorFound = true;
						result += 57;
					}
					break;
				case '}':
					if (c2 != '{')
					{
						errorFound = true;
						result += 1197;
					}
					break;
				case '>':
					if (c2 != '<')
					{
						errorFound = true;
						result += 25137;
					}
					break;
				}
			}

			if (errorFound)
				break;
		}
	}

	return std::to_string(result);
}

std::string Day10::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::vector<long long> pointsList;

	for (const auto& line : input)
	{
		std::stack<char> chars;
		bool errorFound = false;

		for (char c : line)
		{
			if (c == '(' || c == '[' || c == '{' || c == '<')
			{
				chars.push(c);
			}
			else
			{
				char c2 = chars.top();
				chars.pop();

				switch (c)
				{
				case ')':
					if (c2 != '(')
					{
						errorFound = true;
					}
					break;
				case ']':
					if (c2 != '[')
					{
						errorFound = true;
					}
					break;
				case '}':
					if (c2 != '{')
					{
						errorFound = true;
					}
					break;
				case '>':
					if (c2 != '<')
					{
						errorFound = true;
					}
					break;
				}
			}

			if (errorFound)
				break;
		}
		
		if (errorFound)
			continue;

		long long points = 0;

		while (!chars.empty())
		{
			char c = chars.top();
			chars.pop();

			points *= 5;
			switch (c)
			{
			case '(':
				points += 1;
				break;
			case '[':
				points += 2;
				break;
			case '{':
				points += 3;
				break;
			case '<':
				points += 4;
				break;
			}
		}

		pointsList.push_back(points);
	}

	std::sort(pointsList.begin(), pointsList.end(), std::greater<long long>());

	return std::to_string(pointsList[pointsList.size() / 2]);
}