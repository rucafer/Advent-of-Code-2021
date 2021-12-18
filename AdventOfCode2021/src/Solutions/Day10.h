#pragma once
#include "Day.h"
class Day10 : public Day
{
public:
    Day10(const std::string& path) :
        Day(10, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

