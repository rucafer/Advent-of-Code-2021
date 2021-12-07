#pragma once
#include "Day.h"
class Day7 : public Day
{
public:
    Day7(const std::string& path) :
        Day(7, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

