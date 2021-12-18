#include "Day12.h"

#include <unordered_map>
#include <stack>

bool isCorrect(const std::vector<std::string>& path, const std::string& node);

std::string Day12::part1()
{
	auto input = loadFileAsStringList(pathToInput1);
	
	std::unordered_map<std::string, std::vector<std::string>> graph;

	int result = 0;

	for (const auto& line : input)
	{
		auto strs = split(line, "-");
		graph[strs[0]].push_back(strs[1]);
		graph[strs[1]].push_back(strs[0]);
	}

	std::stack<std::vector<std::string>> paths;

	std::vector<std::string> firstRoute;
	firstRoute.push_back("start");
	paths.push(firstRoute);

	bool pathCreated = false;

	while(paths.size() != 0)
	{
		pathCreated = false;

		auto path = paths.top();
		paths.pop();

		for (const auto& node : graph[path[path.size() - 1]])
		{
			if (node == "end")
			{
				result++;
			}
			else if (node != "start")
			{
				//Uppercase
				if (node[0] < 'a')
				{
					std::vector<std::string> pathCopy = path;
					pathCopy.push_back(node);
					paths.push(pathCopy);
				}
				else
				{
					if (std::find(path.begin(), path.end(), node) == path.end())
					{
						std::vector<std::string> pathCopy = path;
						pathCopy.push_back(node);
						paths.push(pathCopy);
					}
				}
			}
		}
	};

	return std::to_string(result);
}

std::string Day12::part2()
{
	auto input = loadFileAsStringList(pathToInput1);

	std::unordered_map<std::string, std::vector<std::string>> graph;

	int result = 0;

	for (const auto& line : input)
	{
		auto strs = split(line, "-");
		graph[strs[0]].push_back(strs[1]);
		graph[strs[1]].push_back(strs[0]);
	}

	std::stack<std::vector<std::string>> paths;
	std::stack<bool> hasTwoLowercase;

	std::vector<std::string> firstRoute;
	firstRoute.push_back("start");
	paths.push(firstRoute);
	hasTwoLowercase.push(false);

	bool pathCreated = false;

	while (paths.size() != 0)
	{
		pathCreated = false;

		auto path = paths.top();
		paths.pop();
		bool twoLC = hasTwoLowercase.top();
		hasTwoLowercase.pop();

		for (const auto& node : graph[path[path.size() - 1]])
		{
			if (node == "end")
			{
				result++;
			}
			else if (node != "start")
			{
				//Uppercase
				if (node[0] < 'a')
				{
					std::vector<std::string> pathCopy = path;
					pathCopy.push_back(node);
					paths.push(pathCopy);
					hasTwoLowercase.push(twoLC);
				}
				else
				{
					if (std::find(path.begin(), path.end(), node) != path.end())
					{
						if (!twoLC)
						{
							std::vector<std::string> pathCopy = path;
							pathCopy.push_back(node);
							paths.push(pathCopy);
							hasTwoLowercase.push(true);
						}
					}
					else
					{
						std::vector<std::string> pathCopy = path;
						pathCopy.push_back(node);
						paths.push(pathCopy);
						hasTwoLowercase.push(twoLC);
					}
				}
			}
		}
	};

	return std::to_string(result);
}

bool isCorrect(const std::vector<std::string>& path, const std::string& node)
{
	if (std::find(path.begin(), path.end(), node) == path.end())
	{
		return true;
	}

	std::vector<std::string> lowercaseNodes;

	for (const auto& n : path)
	{
		if (n[0] >= 'a')
		{
			if (std::find(lowercaseNodes.begin(), lowercaseNodes.end(), n) != lowercaseNodes.end())
			{
				return false;
			}
			lowercaseNodes.push_back(n);
		}
	}
	return true;
}
