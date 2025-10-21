// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_GAME_H_
#define BATTLESHIPPROJECT_GAME_H_

#include "GameMode.h"
#include "GameStatus.h"
#include "Player.h"
#include "RobotPlayer.h"
#include "HumanPlayer.h"
#include "FileWriter.h"
#include "Replay.h"
#include "Utility.h"
#include <string>
#include <typeinfo>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

class Game
{
public:

    static constexpr int kMaxRounds = 10000;

    // Constructor that accepts the names of the two players, the game mode, and the number of rounds
    Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode, int nRounds, const std::string &file_name);

    // Constructor for the replay functionality with on-screen display
    Game(const std::string &filename);

    // Constructor for the replay functionality with file output
    Game(const std::string &filename, const std::string &output);

    // Function that plays an entire game
    void play_game();

    // Function that manages the addition of ships from both players
    void add();

    // Function that adds all ships for a single player
    void add_player_ships(std::unique_ptr<Player> &p);

    // Function that determines which player starts the game
    void first_player();

    // Function that simulates a game round
    void playRound();

    // Function that simulates a single turn of a player
    void play_single_turn(std::unique_ptr<Player> &p, std::unique_ptr<Player> &opp);

    // Function that checks if the user entered map display commands.
    // If so, the command is executed. Returns true if the command was
    // graphical or if the move should be considered invalid for the turn, false otherwise
    bool check_graphic_cmd(std::unique_ptr<Player> &p, const Move &m);

    // Function that handles output printing (screen/file)
    // depending on the game mode
    void handleOutput(const std::string &str);

    // Function that decrements the number of rounds
    int round_terminated() { return numberOfRounds--; }

    // Function that checks if one of the two players has won the game
    // Returns true if one of the players won, false otherwise
    bool Win();

    // Getter method
    int get_rounds() { return numberOfRounds; }

private:
    // Pointers to the two players
    std::unique_ptr<Player> player_1;
    std::unique_ptr<Player> player_2;

    Replay replay;
    FileWriter fw;

    // Constants (number of ships at the start of the game)
    static constexpr int kIronclad = 3;
    static constexpr int kSupportShip = 3;
    static constexpr int kSubmarine = 2;

    // Number of rounds
    int numberOfRounds;
    // Game mode
    GameMode mode;
    // Game status
    GameStatus status;
};

/*
The chrono and thread libraries are useful for making games and replays user-friendly,
adding one-second pauses before a computer move and before each map display.

As required, a game can be played between two computers or between a user and a computer.
Additionally, replay functionalities are available for reading a previously created log file
(from any type of game) and for writing a game to a file (from a log file).
For this reason, four game modes have been defined (ComputerVsComputer, PlayerVsComputer, PrintReplay, WriteReplay),
represented within the GameMode enumerator. Their purpose is to avoid code repetition, 
maintain a common "skeleton" for the game, and distinguish behavior depending on the executable chosen by the user.
*/
#endif
