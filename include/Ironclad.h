//Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_IRONCLAD_H_
#define BATTLESHIPPROJECT_IRONCLAD_H_

#include "Ship.h"
#include "Utility.h"

class Ironclad : public Ship 
{
    public:
        //costruttore
        //crea una nave con corazza = 5, dimensione = 5 e orientamento fornito
        Ironclad(Direction orientation, Position& centre_position, DefenseMap& defense_map, AttackGrid& attack_grid)  : Ship(kSize, orientation, centre_position, defense_map, attack_grid) {}

        //ricordare l'override di action
        bool action(const Position& target, const std::vector<AttackUnit>& data) override;

        //costante che definisce la dimensione della nave corazzata
        static constexpr int kSize = 5;
}; 

/*
classe Ironclad: questa classe rappresenta una nave corazzata, di dimensione 5;
questa nave può eseguire l'operazione di attacco verso una singola cella avversaria, per ridurre di 1 la
corazza di una evenutale nave colpita
*/

#endif