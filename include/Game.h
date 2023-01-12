#ifndef BATTLESHIPPROJECT_GAME_H_
#define BATTLESHIPPROJECT_GAME_H_

#include <string>
#include <typeinfo>
#include "GameMode.h"
#include "Player.h"
#include "RobotPlayer.h"
#include "HumanPlayer.h"
#include "FileWriter.h"
#include "Replay.h"
#include "ReplayType.h"

class Game
{
    public:

    static constexpr int kRoundsComputer = 10;

    //costruttore che accetta i nomi dei due giocatori, la modalità di gioco e il numero di round
    Game(const std::string& nickname_1, const std::string& nickname_2, GameMode mode, int nRounds, const std::string& file_name);

    Game(const std::string& filename);

    Game(const std::string& filename, const std::string& output);

    Game();

    //funzione che simula un turno di gioco
    void playRound();

    //funzione che attesta se uno dei due giocatori ha vinto la partita
    bool Win();

    void add();

    //funzione che stabilisce il giocatore che inizia la partita
    void first_player();

    void play_game();

    int get_rounds() {return numberOfRounds;}
    int round_terminated(){return numberOfRounds--;}

    ~Game(); 

    private:

    //puntatori ai due player
    Player* player_1;
    Player* player_2;
    Replay replay;
    FileWriter fw;

    static constexpr int kIronclad = 3;
    static constexpr int kSupportShip = 3;
    static constexpr int kSubmarine = 2;

    void add_player_ships(Player* p);
    void play_single_turn(Player* p, Player *opponent);


    //numero di turni 
    int numberOfRounds;
    //modalità di gioco
    GameMode mode;

};

#endif