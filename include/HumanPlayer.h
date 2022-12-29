#ifndef BATTLESHIPPROJECT_HUMANPLAYER_H_
#define BATTLESHIPPROJECT_HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer : Player
{
    public:

    //costruttore che crea giocatore con nome
    HumanPlayer(const std::string& nickname) : Player(nickname_){}

    //funzione che dato un comando restituisce una mossa
    Move get_move(const std::string& cmd) override;
    private:
}; 

#endif