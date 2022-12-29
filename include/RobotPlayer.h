#ifndef BATTLESHIPPROJECT_ROBOTPLAYER_H_
#define BATTLESHIPPROJECT_ROBOTPLAYER_H_

#include "Player.h"

class RobotPlayer : public Player
{
    public:

    //costruttore che crea giocatore con nome
    RobotPlayer(const std::string& nickname_) : Player(nickname_){}

    //funzione che dato un comando restituisce una mossa
    Move get_move(const std::string& cmd) override;

    private:

    //funzione che restituisce un indice casuale compreso tra 0 e la dimensione del vettore di navi
    int get_random_index(int size);

    //funzione che restituisce una posizione casuale
    Position& get_random_pos();
}; 

#endif