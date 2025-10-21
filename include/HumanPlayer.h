// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_HUMANPLAYER_H_
#define BATTLESHIPPROJECT_HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer : public Player
{
public:
    // Constructor that creates a player with a name
    HumanPlayer(const std::string &nickname_) : Player(nickname_) {}

    // Function that returns a move given a command
    Move get_move(const std::string &cmd) override;

    // Function that allows adding a ship to the list of ships according to
    // the specifications indicated by the command and the size
    // Returns true if the insertion was successful, false otherwise
    bool add_ships(std::string &cmd, int size) override;

private:
};

#endif
