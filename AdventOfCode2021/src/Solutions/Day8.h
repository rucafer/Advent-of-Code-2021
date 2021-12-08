#pragma once
#include "Day.h"
class Day8 : public Day
{
public:
    Day8(const std::string& path) :
        Day(8, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

