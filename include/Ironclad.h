#ifndef BATTLESHIPPROJECT_IRONCLAD_H_
#define BATTLESHIPPROJECT_IRONCLAD_H_

#include "Ship.h"

class Ironclad : public Ship 
{
    public:
        //costruttore
        //crea una nave con corazza = 5, dimensione = 5 e orientamento fornito
        Ironclad(Direction orientation, Position& centre_position, DefenseMap& defense_map, AttackMap& attack_map)  : Ship(kSize, orientation, centre_position, defense_map, attack_map) {}

        //ricordare l'override di action
        void action(const Position& target, const std::vector<AttackUnit>& data) override;

        //costante che definisce la dimensione della nave corazzata
        static constexpr int kSize = 5;
}; 

#endif