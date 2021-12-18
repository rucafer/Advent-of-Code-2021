#pragma once
#include "Day.h"
class Day13 : public Day
{
public:
    Day13(const std::string& path) :
        Day(13, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

