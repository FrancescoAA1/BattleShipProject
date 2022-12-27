#include "../include/RobotPlayer.h"

RobotPlayer::RobotPlayer(const std::string& nickname) : Player(nickname)
{
}

//il robot inventa la mossa per cui la stringa passata come parametro sarà vuota
Move RobotPlayer::get_move(const std::string& move)
{
    //da implementare
    //restituzione dalla mappa di una nave qualsiasi: serve un metodo?
    //si necessità della posizione del centro della nave e del tipo di nave per la creazione di una mossa
    //scelta di una posizione casuale per il target
    //creazione e ritorno di una nuova mossa
}