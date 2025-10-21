// Author: Francesco Fantin
#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{
    // Check the number of parameters
    // If there are three or four, it relates to a replay functionality

    if (argc == 4 && strcmp(argv[1], "f") == 0)
    {
        // write the replay to another file
        // file to read
        std::string file_name = argv[2];
        // file to write
        std::string output = argv[3];
        try
        {
            Game g{file_name, output};
            // start the game
            g.play_game();
        }
        catch (...)
        {
            std::cerr << "Error reading file: log file corrupted or does not exist" << '\n';
        }
    }
    else if (argc == 3 && strcmp(argv[1], "v") == 0)
    {
        // display the replay file on screen
        // file to read
        std::string file_name = argv[2];
        try
        {
            Game g{file_name};
            // start the game
            g.play_game();
        }
        catch (...)
        {
            std::cerr << "Error reading file: log file corrupted or does not exist" << '\n';
        }
    }
    else
    {
        std::cout << "Invalid parameter list!" << std::endl;
    }

    return 0;
}
