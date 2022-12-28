#include "../include/Player.h"

Player::Player(const std::string& nickname)
{
    nickname_ = nickname;
    sea_map_ = Map();
}


std::vector<AttackUnit> Player::retrieve_unit(const Move& move) 
{
    int nCells;

    //getUnit per Mappa da valutare e implementare 
    //servirebbe nel momento in cui un giocatore deve riferire all'avversario se è stato colpito
    //oppure mandare le coordinate del sonar

    if(move.movetype() == MoveType::attack){ nCells = 1;}
    //else if(move.movetype() == MoveType::moveAndFix){ nCells = 0;}
    else if (move.movetype() == MoveType::moveAndDiscover){ nCells = 25;}
    else { throw InvalidMove{}; }

    //return sea_map_.getUnit(move.target(), nCells);
    return {};
}