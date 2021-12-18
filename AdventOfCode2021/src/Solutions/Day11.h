#pragma once
#include "Day.h"
class Day11 : public Day
{
public:
    Day11(const std::string& path) :
        Day(11, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

