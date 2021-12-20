#include "Day17.h"


struct Goal
{
	int x1, x2, y1, y2;
	Goal(int x1, int x2, int y1, int y2)
		: x1(x1), x2(x2), y1(y1), y2(y2)
	{

	}
};


bool isInBounds(int x, int y, Goal goal);
bool isOverBounds(int x, int y, Goal goal);

std::string Day17::part1()
{
	std::string input = loadFileAsString(pathToInput1);

	int gx1, gx2, gy1, gy2;

	int equal = input.find_first_of('=');
	int dots = input.find_first_of('.');
	int space = input.find_first_of(' ', dots);

	gx1 = std::atoi(input.substr(equal + 1, dots - equal).c_str());
	gx2 = std::atoi(input.substr(dots + 2, space - (dots + 1)).c_str());

	equal = input.find_first_of('=', space);
	dots = input.find_first_of('.', space);
	space = input.find_first_of(' ', dots);

	gy2 = std::atoi(input.substr(equal + 1, dots - equal).c_str());
	gy1 = std::atoi(input.substr(dots + 2, space - (dots + 1)).c_str());

	int startYVel = 1;
	int startXVel = 1;

	bool resultFound = false;

	Goal goal(gx1, gx2, gy1, gy2);

	int velx = startXVel;
	int vely = startYVel;
	int x = 0, y = 0;
	int maxHeight = 0;


	while (startYVel < std::abs(goal.y2))
	{
		bool xVelFound = false;

		while (!xVelFound && startXVel <= goal.x2)
		{
			int newMaxHeight = maxHeight;
			velx = startXVel;
			vely = startYVel;
			x = 0, y = 0;
			while (!isInBounds(x, y, goal) && !isOverBounds(x, y, goal))
			{
				x += velx;
				y += vely;

				if (vely == 0)
					if (y > maxHeight)
						newMaxHeight = y;

				if (velx > 0)
					velx--;

				vely--;
			}

			if (isInBounds(x, y, goal))
			{
				xVelFound = true;
				maxHeight = newMaxHeight;
			}
			else
				startXVel++;
		}

		startXVel = 1;
		startYVel++;
	}

	return std::to_string(maxHeight);
}

std::string Day17::part2()
{
	std::string input = loadFileAsString(pathToInput1);
	int result = 0;

	int gx1, gx2, gy1, gy2;

	int equal = input.find_first_of('=');
	int dots = input.find_first_of('.');
	int space = input.find_first_of(' ', dots);

	gx1 = std::atoi(input.substr(equal + 1, dots - equal).c_str());
	gx2 = std::atoi(input.substr(dots + 2, space - (dots + 1)).c_str());

	equal = input.find_first_of('=', space);
	dots = input.find_first_of('.', space);
	space = input.find_first_of(' ', dots);

	gy2 = std::atoi(input.substr(equal + 1, dots - equal).c_str());
	gy1 = std::atoi(input.substr(dots + 2, space - (dots + 1)).c_str());

	Goal goal(gx1, gx2, gy1, gy2);

	int startYVel = goal.y2;
	int startXVel = 1;

	bool resultFound = false;


	int velx = startXVel;
	int vely = startYVel;
	int x = 0, y = 0;

	while (startYVel < std::abs(goal.y2))
	{
		while (startXVel <= goal.x2)
		{
			velx = startXVel;
			vely = startYVel;
			x = 0, y = 0;
			while (!isInBounds(x, y, goal) && !isOverBounds(x, y, goal))
			{
				x += velx;
				y += vely;

				if (velx > 0)
					velx--;

				vely--;
			}

			if (isInBounds(x, y, goal))
			{
				result++;
			}
			
			startXVel++;
		}

		startXVel = 1;
		startYVel++;
	}

	return std::to_string(result);
}

bool isInBounds(int x, int y, Goal goal)
{
	return x >= goal.x1 && x <= goal.x2 && y <= goal.y1 && y >= goal.y2;
}

bool isOverBounds(int x, int y, Goal goal)
{
	return x > goal.x2 || y < goal.y2;
}