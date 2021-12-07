#pragma once
#include "Day.h"
class Day6 : public Day
{
public:
    Day6(const std::string& path) :
        Day(6, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

