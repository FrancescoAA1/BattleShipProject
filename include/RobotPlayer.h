// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_ROBOTPLAYER_H_
#define BATTLESHIPPROJECT_ROBOTPLAYER_H_

#include "Player.h"
#include "Utility.h"
#include <chrono>
#include <thread>

class RobotPlayer : public Player
{
public:
    // Constructor that creates a player with a name
    RobotPlayer(const std::string &nickname_) : Player(nickname_) {}

    // Function that, given a command, returns a move
    Move get_move(const std::string &cmd) override;

    // Function to add ships to the player's fleet
    bool add_ships(std::string &cmd, int size) override;

private:
    // Function that returns a random position
    Position get_random_pos();

    // Function that returns a valid random position at (size) distance along a single axis from (origin)
    Position get_random_pos(const Position &origin, int size);
};

#endif
