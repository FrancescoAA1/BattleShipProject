#ifndef BATTLESHIPPROJECT_MAP_H_
#define BATTLESHIPPROJECT_MAP_H_

#include "Position.h"
#include "DefenseUnit.h"
#include "AttackUnit.h"
#include "Ship.h"
#include "Submarine.h"
#include "Ironclad.h"
#include "SupportShip.h"
#include <unordered_map>

class Map
{
    public: 


    private: 
    // Regione delle costanti da utilizzare nella classe  
    static constexpr int kHeight = 12; 
    static constexpr int kWidth = 12; 
    // rappresenta la mappa da usare per la difesa
    DefenseUnit defense_map_[kHeight][kWidth]; 
    // rappresenta la mappa da usare per l'attacco
    AttackUnit attack_map[kHeight][kWidth]; 
    // collezione associativa di navi con Key = posizione del centro e value = puntatore a generica nave
    std::unordered_map<Position, Ship*> ship_dictionary; 

}; 

#endif
