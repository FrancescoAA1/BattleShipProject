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

    //funzione che simula un turno di gioco
    void playRound();

    //funzione che attesta se uno dei due giocatori ha vinto la partita
    bool Win();

    void add();

    private:

    //puntatori ai due player
    Player* player_1;
    Player* player_2;

    static constexpr int kIronclad = 3;
    static constexpr int kSupportShip = 3;
    static constexpr int kSubmarine = 2;


    //numero di turni 
    int numberOfRounds;
    //modalità di gioco
    GameMode mode;

};

#endif