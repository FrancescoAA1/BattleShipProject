// Author: Enrico Disarò
#include "../include/Utility.h"

// Overload of the << operator that writes the defense matrix to the output stream
std::string visual_merge_grid(const AttackGrid &attack_grid, const DefenseMap &defense_map)
{
    // get all the lines that make up the maps by splitting them on the newline character
    std::vector<std::string> line_d_map = splitstr(defense_map.to_string(), "\n");
    std::vector<std::string> line_a_grid = splitstr(attack_grid.to_string(), "\n");

    // now merge them line by line
    std::string result = "";
    int i = 0;
    int j = 0;

    while (i < line_d_map.size() && j < line_a_grid.size())
    {
        result += line_d_map[i];
        result += "        ";
        result += line_a_grid[j];
        result += "\n";
        i++;
        j++;
    }
    return result;
}

// function to split strings on a specific character
std::vector<std::string> splitstr(std::string str, std::string delim)
{
    std::vector<std::string> out{};
    int start = 0;
    // search for the position of the first delimiter, if present
    int end = str.find(delim);

    while (end != -1)
    {
        // found a delimiter
        // add the substring to the vector up to that point and proceed to the next search
        out.push_back(str.substr(start, end - start));
        start = end + delim.size();
        end = str.find(delim, start);
    }
    // add the last one
    out.push_back(str.substr(start, end - start));

    return out;
}

int get_random(int range)
{
    static int counter = 0;
    int temp = 0;

    if (counter % 2 == 0)
    {
        std::srand(time(NULL));
        temp = (std::rand() + counter) % range;
    }

    else
    {
        std::srand(1);
        temp = (std::rand() + counter) % range;
    }

    counter++;
    return temp;
}

Position convert_to_position(const std::string &coordinate)
{
    Position pos{};

    try
    {
        // subtraction of the ASCII value of 'A' from the first character of the string
        // conversion from char to int
        int y;
        // if the columns are J or K, then it's invalid and return invalid
        if (coordinate[0] == 'J' || coordinate[0] == 'K')
        {
            pos.make_absolute_invalid();
            return pos;
        }
        if (coordinate[0] > 'J') // skip columns j and k
            y = coordinate[0] - kDefaultCapitalAscii - 2;
        else
            y = coordinate[0] - kDefaultCapitalAscii;

        // conversion from string to integer of the last part of the coordinate pair (number)
        // stoi throws std::invalid_argument exception if the substring is not a number
        std::string x_pos = coordinate.substr(1, coordinate.size() - 1);
        int x = std::stoi(x_pos) - 1;

        // check that the digits of the original number (i.e., y+1) are equal in count 
        // to the length of the previously extracted substring
        if (count_digits(x + 1) != x_pos.size())
        {
            pos.make_absolute_invalid();
            return pos;
        }

        // check that x and y are within the size range of the two maps
        // NOTE: it would be appropriate to be able to access the map size constants
        if (x >= 0 && x <= DefenseMap::kWidth && y >= 0 && y <= DefenseMap::kHeight)
        {
            pos = Position(x, y);
            return pos;
        }
        else
        {
            // if one of the two coordinates is invalid, return invalid position
            pos.make_absolute_invalid();
            return pos;
        }
    }
    catch (std::invalid_argument)
    {
        pos.make_absolute_invalid();
        return pos;
    }
}

std::string convert_to_command(const Position &position)
{
    if (position.X() >= 0 && position.X() <= DefenseMap::kWidth && position.Y() >= 0 && position.Y() <= DefenseMap::kHeight)
    {

        // explicit conversion from int to char (safe) of the X coordinate of the position
        // string formed by the character obtained by adding the ASCII value of "A"
        std::string letter(1, (char)position.Y() + kDefaultCapitalAscii);
        if (letter[0] >= 'J')
            letter[0] = letter[0] + 2;

        // conversion from int to string of the Y coordinate of the position
        std::string number = std::to_string(position.X() + 1);

        // concatenation of the two strings containing the coordinates in (A1) format
        std::string coordinate = letter + number;
        return coordinate;
    }
    else
        return "";
}

int count_digits(int n)
{
    if (n / 10 == 0)
        return 1;
    return 1 + count_digits(n / 10);
}
