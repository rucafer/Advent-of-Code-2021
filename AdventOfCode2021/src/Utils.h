#pragma once
#include <iostream>
#include <fstream>
#include <vector>

//GLOBAL CONSTANTS AND PROGRAM SETTINGS
extern bool writeDebuggingInfo;

#define print_yellow() std::cout << "\x1B[33m"
#define print_green() std::cout << "\x1B[32m"
#define print_red() std::cout << "\x1B[31m"
#define print_default() std::cout << "\033[0m"

#define	PART_ONE_HEADER "\x1B[32m***\x1B[31mo\x1B[32m***\x1B[31mo\x1B[32m***\x1B[31m PART 1 \x1B[32m***\x1B[31mo\x1B[32m***\x1B[31mo\x1B[32m***\033[0m"
#define	PART_TWO_HEADER "\x1B[32m***\x1B[31mo\x1B[32m***\x1B[31mo\x1B[32m***\x1B[31m PART 2 \x1B[32m***\x1B[31mo\x1B[32m***\x1B[31mo\x1B[32m***\033[0m"

std::string getDayHeader(int dayNumber);

std::vector<int> loadFileAsIntList(const std::string& file);
std::vector<int> loadFileAsIntListComma(const std::string& file);
std::vector<long long> loadFileAsLongList(const std::string& file);
std::vector<std::string> loadFileAsStringList(const std::string& file);
std::string loadFileAsString(const std::string& file);

std::vector<std::string> split(const std::string& input, const std::string& token);