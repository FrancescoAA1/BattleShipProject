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

    //funzione che permette di aggiungere una nave alla lista di navi secondo 
    //le specifiche indicate dal comando e dalla taglia
    //restituisce true se l'inserimento è andato a buon fine, false altrimenti
    bool add_ships(const std::string &cmd, int size, FileWriter& fw) override;

private:
};

#endif