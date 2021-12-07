#pragma once
#include "Day.h"
class Day5 : public Day
{
public:
    Day5(const std::string& path) :
        Day(5, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

