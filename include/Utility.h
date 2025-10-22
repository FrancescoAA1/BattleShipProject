// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_UTILITY_H_
#define BATTLESHIPPROJECT_UTILITY_H_

#include "DefenseMap.h"
#include "AttackGrid.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

// File of utility functions to be used in multiple parts of the project

// Function to split strings by a given character
std::vector<std::string> splitstr(std::string str, std::string delim = " ");

// Overload of the << operator that writes the defense matrix to the output stream
std::string visual_merge_grid(const AttackGrid &attack_grid, const DefenseMap &defense_map);

// Function that converts a pair of coordinates (i.e., one part of the full command)
// into a Position
Position convert_to_position(const std::string &coordinate);

// Function that converts a Position into one part of the command
std::string convert_to_command(const Position &position);

// Function to get a random number in a slightly more random way between 0 and range - 1
int get_random(int range);

// Function that counts the number of digits in a number
int count_digits(int n);

// Constant useful for conversions from command to position and vice versa
static constexpr int kDefaultCapitalAscii = 65;
#endif

/*
The Utility class provides methods used by multiple classes that do not require access
to the private fields of those classes.
For more information about the methods, see the comments in Utility.h
*/
