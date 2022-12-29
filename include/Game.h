#ifndef BATTLESHIPPROJECT_GAME_H_
#define BATTLESHIPPROJECT_GAME_H_

#include <string>
#include "GameMode.h"
#include "Player.h"
#include "RobotPlayer.h"
#include "HumanPlayer.h"

class Game
{
    public:

    Game(const std::string& nickname_1, const std::string& nickname_2, GameMode mode, int nRounds);

    void playRound();

    bool Win();

    private:

    Player* player_1;
    Player* player_2;

    int numberOfRounds;
    GameMode mode;

};

#endif