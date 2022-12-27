#ifndef BATTLESHIPPROJECT_HUMANPLAYER_H_
#define BATTLESHIPPROJECT_HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer : Player
{
    public:

    HumanPlayer(const std::string& nickname_);
    Move get_move(const std::string&) override;
}; 

#endif