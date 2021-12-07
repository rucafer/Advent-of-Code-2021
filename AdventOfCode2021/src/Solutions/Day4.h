#pragma once
#include "Day.h"
class Day4 : public Day
{
public:
    Day4(const std::string& path) :
        Day(4, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

