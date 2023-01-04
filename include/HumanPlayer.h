#ifndef BATTLESHIPPROJECT_HUMANPLAYER_H_
#define BATTLESHIPPROJECT_HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer : public Player
{
public:
    // costruttore che crea giocatore con nome
    HumanPlayer(const std::string &nickname_) : Player(nickname_) {}

    // funzione che dato un comando restituisce una mossa
    Move get_move(const std::string &cmd) override;

    bool add_ships(const std::string &cmd, int size) override;

    ~HumanPlayer() override; 


private:
};

#endif