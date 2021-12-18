#pragma once
#include "Day.h"
class Day14 : public Day
{
public:
    Day14(const std::string& path) :
        Day(14, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

