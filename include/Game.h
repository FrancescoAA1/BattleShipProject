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

    //costruttore che accetta i nomi dei due giocatori, la modalità di gioco e il numero di round
    Game(const std::string& nickname_1, const std::string& nickname_2, GameMode mode, int nRounds);

    //funzione che 
    void playRound();

    //funzione che attesta se uno dei due giocatori ha vinto la partita
    bool Win();

    private:

    //puntatori ai due player
    Player* player_1;
    Player* player_2;

    //numero di turni 
    int numberOfRounds;
    //modalità di gioco
    GameMode mode;

};

#endif