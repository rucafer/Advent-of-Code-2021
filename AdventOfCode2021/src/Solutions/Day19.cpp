#include "Day19.h"

#include <unordered_map>
#include <queue>

struct Point
{
	int x, y, z;

	Point(int x, int y, int z)
		:x(x), y(y), z(z)
	{

	}

	Point()
		: x(0), y(0), z(0)
	{

	}

	Point(const std::string& str)
	{
		std::vector<std::string> spl = split(str, ",");
		x = std::atoi(spl[0].c_str());
		y = std::atoi(spl[1].c_str());
		z = std::atoi(spl[2].c_str());
	}

	bool operator== (const Point& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	int distance(const Point& other)
	{
		return std::abs(x - other.x) + std::abs(y - other.y) + std::abs(z - other.z);
	}

};

struct OverlapDetails
{
	int xOffset, yOffset, zOffset;
	int Rot;
	int sc1, sc2;

	OverlapDetails(int xOffset, int yOffset, int zOffset, int Rot, int sc1, int sc2)
		: xOffset(xOffset), yOffset(yOffset), zOffset(zOffset), Rot(Rot), sc1(sc1), sc2(sc2)
	{

	}

	OverlapDetails()
		:xOffset(0), yOffset(0), zOffset(0), Rot(Rot), sc1(0), sc2(0)
	{

	}

};

/*struct PointPair
{
	Point& pointA, pointB;

	PointPair(Point& pointA, Point& pointB)
		: pointA(pointA), pointB(pointB)
	{

	}
};*/

bool checkOverlap(const std::vector<std::vector<Point>>& beacons, int scanner, int referenceScanner, int rot, OverlapDetails* result);
Point rotate(int rot, Point p);

std::string Day19::part1()
{
	return "a";
	std::vector<std::vector<Point>> beacons;
	std::unordered_map<int, OverlapDetails> results;

	std::vector<Point> finalBeacons;

	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int currentScanner = 0;
	for (const auto& line : input)
	{
		if (line.empty())
			continue;

		if (line.find("--- scanner") != std::string::npos )
		{
			currentScanner++;
			beacons.emplace_back();
			continue;
		}

		beacons[currentScanner - 1].emplace_back(line);
	}

	std::queue<int> visitedScanenrs;
	visitedScanenrs.push(0);

	std::vector<int> remainingScanners;
	for (size_t i = 1; i < beacons.size(); i++)
	{
		remainingScanners.push_back(i);
	}


	while (!visitedScanenrs.empty() && !remainingScanners.empty())
	{
		int referenceScanner = visitedScanenrs.front();
		visitedScanenrs.pop();

		std::vector<int>::iterator it = remainingScanners.begin();
		while (it != remainingScanners.end())
		{
			bool overlapFound = false;
			int scanner = *it;
			for (int rot = 0; rot < 24; rot++)
			{
				OverlapDetails od;
				if (checkOverlap(beacons, scanner, referenceScanner, rot, &od))
				{
					results[scanner] = od;

					visitedScanenrs.push(scanner);
					it = remainingScanners.erase(it);
					overlapFound = true;
					break;
				}
			}

			if (!overlapFound)
				it++;
		}
	}

	for (size_t i = 0; i < beacons.size(); i++)
	{
		int sc = i;
		while (sc != 0)
		{
			OverlapDetails& od = results[sc];
			sc = od.sc2;

			for (Point& p : beacons[i])
			{
				p = rotate(od.Rot, p);
				p.x += od.xOffset;
				p.y += od.yOffset;
				p.z += od.zOffset;
			}
		}

		for (const Point& p : beacons[i])
		{
			if (std::find(finalBeacons.begin(), finalBeacons.end(), p) == finalBeacons.end())
			{
				finalBeacons.push_back(p);
			}
		}
		
	}

	return std::to_string(finalBeacons.size());
}

std::string Day19::part2()
{
	std::vector<std::vector<Point>> beacons;
	std::unordered_map<int, OverlapDetails> results;

	std::vector<Point> offsets;

	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	int currentScanner = 0;
	for (const auto& line : input)
	{
		if (line.empty())
			continue;

		if (line.find("--- scanner") != std::string::npos)
		{
			currentScanner++;
			beacons.emplace_back();
			continue;
		}

		beacons[currentScanner - 1].emplace_back(line);
	}

	std::queue<int> visitedScanenrs;
	visitedScanenrs.push(0);

	std::vector<int> remainingScanners;
	for (size_t i = 1; i < beacons.size(); i++)
	{
		remainingScanners.push_back(i);
	}


	while (!visitedScanenrs.empty() && !remainingScanners.empty())
	{
		int referenceScanner = visitedScanenrs.front();
		visitedScanenrs.pop();

		std::vector<int>::iterator it = remainingScanners.begin();
		while (it != remainingScanners.end())
		{
			bool overlapFound = false;
			int scanner = *it;
			for (int rot = 0; rot < 24; rot++)
			{
				OverlapDetails od;
				if (checkOverlap(beacons, scanner, referenceScanner, rot, &od))
				{
					results[scanner] = od;

					visitedScanenrs.push(scanner);
					it = remainingScanners.erase(it);
					overlapFound = true;
					break;
				}
			}

			if (!overlapFound)
				it++;
		}
	}

	for (size_t i = 0; i < beacons.size(); i++)
	{
		int sc = i;
		Point p(0, 0, 0);

		while (sc != 0)
		{
			OverlapDetails& od = results[sc];
			sc = od.sc2;


			p = rotate(od.Rot, p);
			p.x += od.xOffset;
			p.y += od.yOffset;
			p.z += od.zOffset;
		}

		offsets.push_back(p);
		//std::cout << "Scanner " << i << " offset: x: " << p.x << " y: " << p.y << " z: " << p.z << std::endl;
	}

	int max = 0;
	for (size_t i = 0; i < offsets.size(); i++)
	{
		for (size_t j = 0; j < offsets.size(); j++)
		{
			if (i != j)
			{
				int dist = 0;
				dist += std::abs(offsets[i].x - offsets[j].x);
				dist += std::abs(offsets[i].y - offsets[j].y);
				dist += std::abs(offsets[i].z - offsets[j].z);

				if (dist > max)
					max = dist;
			}
		}
	}

	return std::to_string(max);
}

bool checkOverlap(const std::vector<std::vector<Point>>& beacons, int scanner, int referenceScanner, int rot, OverlapDetails* result)
{
	for (const Point& p1 : beacons[scanner])
	{
		for (const Point& p2 : beacons[referenceScanner])
		{
			Point p1Rot = rotate(rot, p1);

			//Calculate offset that makes p1 and p2 equal
			int xOffset = p2.x - p1Rot.x;
			int yOffset = p2.y - p1Rot.y;
			int zOffset = p2.z - p1Rot.z;

			int overlapsFound = 0;

			int pointsChecked = 0;
			for (const Point& cmp1 : beacons[scanner])
			{
				if (beacons[scanner].size() - pointsChecked + overlapsFound < 12)
					break;
				for (const Point& cmp2 : beacons[referenceScanner])
				{
					Point p1cpy = rotate(rot, cmp1);


					if (p1cpy.x + xOffset == cmp2.x && p1cpy.y + yOffset == cmp2.y && p1cpy.x + xOffset == cmp2.x)
					{
						overlapsFound++;
						if (overlapsFound == 12)
						{
							result->xOffset = xOffset;
							result->yOffset = yOffset;
							result->zOffset = zOffset;
							result->Rot = rot;
							result->sc1 = scanner;
							result->sc2 = referenceScanner;
							return true;
						}
					}
				}

				pointsChecked++;
			}
		}
	}

	return false;
}

Point rotate(int rot, Point p)
{
	int tmp;

	switch (rot)
	{
	case 0:
		break;
	case 1:
		tmp = p.z;
		p.z = -p.y;
		p.y = tmp;
		break;
	case 2:
		tmp = p.z;
		p.z = -p.z;
		p.y = -p.y;
		break;
	case 3:
		tmp = p.z;
		p.z = p.y;
		p.y = -tmp;
		break;


	case 4:
		p.x = -p.x;
		p.y = -p.y;
		break;
	case 5:
		p.x = -p.x;
		tmp = p.z;
		p.z = p.y;
		p.y = tmp;
		break;
	case 6:
		p.x = -p.x;
		p.z = -p.z;
		break;
	case 7:
		p.x = -p.x;
		tmp = p.z;
		p.z = -p.y;
		p.y = -tmp;
		break;


	case 8:
		tmp = p.x;
		p.x = p.y;
		p.y = -tmp;
		break;
	case 9:
		tmp = p.x;
		p.x = p.y;
		p.y = p.z;
		p.z = tmp;
		break;
	case 10:
		tmp = p.x;
		p.x = p.y;
		p.y = tmp;
		p.z = -p.z;
		break;
	case 11:
		tmp = p.x;
		p.x = p.y;
		p.y = -p.z;
		p.z = -tmp;
		break;


	case 12:
		tmp = p.x;
		p.x = -p.y;
		p.y = tmp;
		break;
	case 13:
		tmp = p.x;
		p.x = -p.y;
		p.y = p.z;
		p.z = -tmp;
		break;
	case 14:
		tmp = p.x;
		p.x = -p.y;
		p.y = -tmp;
		p.z = -p.z;
		break;
	case 15:
		tmp = p.x;
		p.x = -p.y;
		p.y = -p.z;
		p.z = tmp;
		break;


	case 16:
		tmp = p.x;
		p.x = p.z;
		p.z = -tmp;
		break;
	case 17:
		tmp = p.x;
		p.x = p.z;
		p.z = -p.y;
		p.y = -tmp;
		break;
	case 18:
		tmp = p.x;
		p.x = p.z;
		p.z = tmp;
		p.y = -p.y;
		break;
	case 19:
		tmp = p.x;
		p.x = p.z;
		p.z = p.y;
		p.y = tmp;
		break;


	case 20:
		tmp = p.x;
		p.x = -p.z;
		p.z = tmp;
		break;
	case 21:
		tmp = p.x;
		p.x = -p.z;
		p.z = -p.y;
		p.y = tmp;
		break;
	case 22:
		tmp = p.x;
		p.x = -p.z;
		p.z = -tmp;
		p.y = -p.y;
		break;
	case 23:
		tmp = p.x;
		p.x = -p.z;
		p.z = p.y;
		p.y = -tmp;
		break;


	default:
		break;
	}

	return p;
}