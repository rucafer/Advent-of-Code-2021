#pragma once
#include "Day.h"
class Day15 : public Day
{
public:
    Day15(const std::string& path) :
        Day(15, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

