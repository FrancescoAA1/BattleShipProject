#ifndef BATTLESHIPPROJECT_MOVE_H_
#define BATTLESHIPPROJECT_MOVE_H_

#include <string>
#include "Position.h"

//enumeratore che indica il tipo di mossa effettuata dal giocatore
enum MoveType{
    addShip, //aggiunta di una nave
    attack, //attacco (corazzata)
    moveAndFix, //spostamento e cura (nave di supporto)
    moveAndDiscover, //spostamento ed ispezione (sottomarino)
    showMap, //stampa delle mappe del giocatore (con posizione target e origine poste a null)
    clearMap //pulizia della mappa
};

class Move
{
    public:
    //costruttore valido sia per Human Player, sia per Robot Player
    Move(const Position&, const Position&, MoveType);

    //metodi getter
    Position origin() const {return origin_;}
    Position target() const {return target_;}
    MoveType movetype() const {return move_;}

    private: 

    //posizione da cui viene effettuata la mossa
    Position origin_;
    //posizione su cui deve essere effettuata la mossa
    Position target_;
    //tipologia di mossa
    MoveType move_;
}; 

/*
Classe Move: rappresenta una mossa effettuata da un qualsiasi giocatore.
*/
#endif