#pragma once
#include "Day.h"
class Day18 : public Day
{
public:
    Day18(const std::string& path) :
        Day(18, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};
