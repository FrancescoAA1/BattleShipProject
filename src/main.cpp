// Author: Francesco Fantin
#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>
int main(int argc, char **argv)
{

    // Check the number of parameters
    // If there are two, it means it is a PlayerVsComputer
    // or ComputerVsComputer match

    if (argc == 2)
    {
        // player vs computer match
        if (strcmp(argv[1], "pc") == 0)
        {
            std::string name;
            std::cout << "Enter your name: ";
            getline(std::cin, name);

            std::cout << "Enter the maximum number of moves: ";
            int nRounds;
            std::string line;

            bool done = false;
            while (!done)
            {
                try
                {
                    getline(std::cin, line);
                    nRounds = std::stoi(line);
                    if (count_digits(nRounds) == line.size() && nRounds < Game::kMaxRounds)
                    {
                        done = true;
                    }
                    else
                    {
                        done = false;
                        std::cout << "Error! Invalid format or exceeds the maximum move limit.\nPlease re-enter the maximum number of moves: ";
                    }
                }
                catch (std::invalid_argument &ex)
                {
                    std::cout << "Error! Invalid format or exceeds the maximum move limit.\nPlease re-enter the maximum number of moves: ";
                }
            }

            std::string file_name;
            std::cout << "Enter the name of the log file: ";
            getline(std::cin, file_name);

            Game g{name, "ComputerX", GameMode::PlayerVsComputer, nRounds, file_name};
            // start match
            g.play_game();
        }

        // computer vs computer match
        else if (strcmp(argv[1], "cc") == 0)
        {
            std::cout << "Enter the maximum number of moves: ";
            int nRounds;
            std::string line;

            bool done = false;
            while (!done)
            {
                try
                {
                    getline(std::cin, line);
                    nRounds = std::stoi(line);
                    if (count_digits(nRounds) == line.size() && nRounds < Game::kMaxRounds)
                    {
                        done = true;
                    }
                    else
                    {
                        done = false;
                        std::cout << "Error! Invalid format or exceeds the maximum move limit.\nPlease re-enter the maximum number of moves: ";
                    }
                }
                catch (std::invalid_argument &ex)
                {
                    std::cout << "Error! Invalid format or exceeds the maximum move limit.\nPlease re-enter the maximum number of moves: ";
                }
            }

            std::string file_name;
            std::cout << "Enter the name of the log file: ";
            getline(std::cin, file_name);

            Game g{"ComputerX", "ComputerY", GameMode::ComputerVsComputer, nRounds, file_name};
            g.play_game();
        }
    }
    else
    {
        std::cout << "Incorrect parameter list" << std::endl;
    }

    return 0;
}
