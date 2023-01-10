#ifndef BATTLESHIPPROJECT_ROBOTPLAYER_H_
#define BATTLESHIPPROJECT_ROBOTPLAYER_H_

#include "Player.h"
#include <stdlib.h>
#include <time.h>

class RobotPlayer : public Player
{
    public:

    //costruttore che crea giocatore con nome
    RobotPlayer(const std::string& nickname_) : Player(nickname_){}

    //funzione che dato un comando restituisce una mossa
    Move get_move(const std::string& cmd) override;

    bool add_ships(const std::string& cmd, int size) override;

    private:

    //funzione che restituisce una posizione casuale
    Position get_random_pos();
    
    //funzione che restituisce una posizionie casuale valida a (size) distanza su un solo asse da (origin)
    Position get_random_pos(const Position& origin, int size);
}; 

#endif