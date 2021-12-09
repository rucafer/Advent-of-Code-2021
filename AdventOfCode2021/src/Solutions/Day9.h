#pragma once
#include "Day.h"
class Day9 : public Day
{
public:
    Day9(const std::string& path) :
        Day(9, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

