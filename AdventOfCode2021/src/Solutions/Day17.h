#pragma once
#include "Day.h"
class Day17 : public Day
{
public:
    Day17(const std::string& path) :
        Day(17, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

