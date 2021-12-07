#pragma once
#include "Day.h"
class Day2 : public Day
{
public:
    Day2(const std::string& path):
        Day(2, path){ }

    std::string part1() override;
    std::string part2() override;
};

