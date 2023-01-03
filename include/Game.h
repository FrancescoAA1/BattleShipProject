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

    static constexpr int kRoundsComputer = 10;

    //costruttore che accetta i nomi dei due giocatori, la modalità di gioco e il numero di round
    Game(const std::string& nickname_1, const std::string& nickname_2, GameMode mode, int nRounds);

    Game();

    //funzione che simula un turno di gioco
    void playRound();

    //funzione che attesta se uno dei due giocatori ha vinto la partita
    bool Win();

    void add();

    int get_rounds() {return numberOfRounds;}
    int round_terminated(){return numberOfRounds--;}

    private:

    //puntatori ai due player
    Player* player_1;
    Player* player_2;

    static constexpr int kIronclad = 3;
    static constexpr int kSupportShip = 3;
    static constexpr int kSubmarine = 2;

    void add_player_ships(Player* p);
    void play_single_turn(Player* p);


    //numero di turni 
    int numberOfRounds;
    //modalità di gioco
    GameMode mode;

};

#endif