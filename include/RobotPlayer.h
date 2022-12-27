#ifndef BATTLESHIPPROJECT_ROBOTPLAYER_H_
#define BATTLESHIPPROJECT_ROBOTPLAYER_H_

#include "Player.h"

class RobotPlayer : Player
{
    public:

    RobotPlayer(const std::string& nickname_);
    Move get_move(const std::string&) override;
}; 

#endif