//Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_MOVE_H_
#define BATTLESHIPPROJECT_MOVE_H_

#include <string>
#include "Position.h"
#include "Utility.h"

//enumeratore che indica il tipo di mossa effettuata dal giocatore
enum MoveType{
    invalid,
    attack, //attacco (corazzata)
    moveAndFix, //spostamento e cura (nave di supporto)
    moveAndDiscover, //spostamento ed ispezione (sottomarino)
    showMap, //stampa delle mappe del giocatore
    clearEmptyHit, //rimozione dei simboli 'O' dalla mappa del giocatore
    clearFullHit, //rimozione dei simboli 'X' dalla mappa del giocatore
    clearSonared //rimozione dei simboli 'Y' dalla mappa del giocatore
};

class Move
{
    public:
    //costruttore valido sia per Human Player, sia per Robot Player
    Move(const Position&, const Position&, MoveType);

    //costruttore che creare una mossa invalida
    Move();


    //metodi getter
    Position origin() const {return origin_;}
    Position target() const {return target_;}
    MoveType movetype() const {return move_;}

    //metodi setter
    void set_movetype(MoveType m){move_ = m;}
    void set_origin(const Position& origin){origin_ = origin;}
    void set_target(const Position& target){target_ = target;}

    //rende non valida una mossa invalidandone le posizioni e cambiando il tipo di mossa
    void makeInvalid();


    // converte a stringa la mossa
    std::string to_string() const; 

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