#pragma once
#include "Day.h"
class Day19 : public Day
{
public:
    Day19(const std::string& path) :
        Day(19, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};
