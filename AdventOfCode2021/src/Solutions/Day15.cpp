#include "Day15.h"

#include <queue>
#include <unordered_map>

class Point
{
public:
	int x, y;
	int prioriry;

	bool operator<(const Point& p1) const
	{
		return prioriry < p1.prioriry;
	}

	bool operator>(const Point& p1) const
	{
		return prioriry > p1.prioriry;
	}

	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}

	Point(int x, int y) 
		: x(x), y(y), prioriry(0)
	{

	}

	Point()
		: x(0), y(0), prioriry(0)
	{

	}
};

struct PointHasher
{
	std::size_t operator()(const Point& p) const
	{
		using std::size_t;
		using std::hash;
		using std::string;

		return ((hash<int>()(p.x)
			^ (hash<int>()(p.y) << 1)) >> 1);
	}
};

int heuristicCost(const Point& a, const Point& b);


//A*
std::string Day15::part1()
{
	std::vector<std::string> inputStr = loadFileAsStringList(pathToInput1);

	int rows = inputStr.size();
	int cols = inputStr[0].size();

	int** grid = new int* [cols];
	for (int i = 0; i < cols; i++)
	{
		grid[i] = new int[rows];

		for (int j = 0; j < rows; j++)
		{
			grid[i][j] = inputStr[j][i] - '0';
		}
	}

	std::unordered_map<Point, Point, PointHasher> cameFrom;
	std::unordered_map<Point, int, PointHasher> costSoFar;

	Point goal(cols - 1, rows - 1);

	std::priority_queue <Point, std::vector<Point>, std::greater<Point>> remainingPts;
	remainingPts.push(Point(0, 0));

	cameFrom[Point(0, 0)] = Point(0, 0);
	costSoFar[Point(0, 0)] = 0;

	while (!remainingPts.empty())
	{
		Point current = remainingPts.top();
		remainingPts.pop();

		if (current == Point(cols - 1, rows - 1))
			break;

		//Top
		if (current.y > 0)
		{
			Point next = Point(current.x, current.y - 1);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Bottom
		if (current.y < rows - 1)
		{
			Point next = Point(current.x, current.y + 1);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Left
		if (current.x > 0)
		{
			Point next = Point(current.x - 1, current.y);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Right
		if (current.x < cols - 1)
		{
			Point next = Point(current.x + 1, current.y);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}
	}
	

	return std::to_string(costSoFar[goal]);
}

std::string Day15::part2()
{
	std::vector<std::string> inputStr = loadFileAsStringList(pathToInput1);

	int oldRows = inputStr.size();
	int oldCols = inputStr[0].size();

	int rows = oldRows * 5;
	int cols = oldCols * 5;

	int** grid = new int* [cols];
	for (int i = 0; i < cols; i++)
	{
		grid[i] = new int[rows];
	}

	for (int i = 0; i < oldRows; i++)
	{
		for (int j = 0; j < oldCols; j++)
		{
			grid[i][j] = inputStr[j][i] - '0';
		}
	}

	for (int i = 0; i < cols; i++)
	{
			for (int j = 0; j < rows; j++)
			{
				if (j >= oldRows || i >= oldCols)
				{
					int value = grid[i % oldCols][j % oldRows];
					value += j / oldCols + i / oldRows;
					while (value >= 10)
						value -= 9;
					grid[i][j] = value;
				}
			}
	}

	std::unordered_map<Point, Point, PointHasher> cameFrom;
	std::unordered_map<Point, int, PointHasher> costSoFar;

	Point goal(cols - 1, rows - 1);

	std::priority_queue <Point, std::vector<Point>, std::greater<Point>> remainingPts;
	remainingPts.push(Point(0, 0));

	cameFrom[Point(0, 0)] = Point(0, 0);
	costSoFar[Point(0, 0)] = 0;

	while (!remainingPts.empty())
	{
		Point current = remainingPts.top();
		remainingPts.pop();

		if (current == Point(cols - 1, rows - 1))
			break;

		//Top
		if (current.y > 0)
		{
			Point next = Point(current.x, current.y - 1);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Bottom
		if (current.y < rows - 1)
		{
			Point next = Point(current.x, current.y + 1);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Left
		if (current.x > 0)
		{
			Point next = Point(current.x - 1, current.y);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}

		//Right
		if (current.x < cols - 1)
		{
			Point next = Point(current.x + 1, current.y);
			int newCost = costSoFar[current] + grid[next.x][next.y];
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priorty = newCost + heuristicCost(next, goal);
				next.prioriry = priorty;
				remainingPts.push(next);
				cameFrom[next] = current;
			}
		}
	}


	return std::to_string(costSoFar[goal]);
}

//Manhattan distance
int heuristicCost(const Point& a, const Point& b)
{
	return std::abs(a.x- b.x) + std::abs(a.y - b.y);
}