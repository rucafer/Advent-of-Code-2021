#pragma once
#include "Day.h"
class Day3 : public Day
{
public:
    Day3(const std::string& path) :
        Day(3, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

