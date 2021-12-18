#pragma once
#include "Day.h"
class Day12 : public Day
{
public:
    Day12(const std::string& path) :
        Day(12, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

