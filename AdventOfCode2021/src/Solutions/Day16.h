#pragma once
#include "Day.h"
class Day16 : public Day
{
public:
    Day16(const std::string& path) :
        Day(16, path)
    {
    }

    std::string part1() override;
    std::string part2() override;
};

