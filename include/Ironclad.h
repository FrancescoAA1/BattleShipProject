// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_IRONCLAD_H_
#define BATTLESHIPPROJECT_IRONCLAD_H_

#include "Ship.h"
#include "Utility.h"

class Ironclad : public Ship 
{
public:
    // Constructor
    // Creates a ship with armor = 5, size = 5, and the given orientation
    Ironclad(Direction orientation, Position& centre_position, DefenseMap& defense_map, AttackGrid& attack_grid)  
        : Ship(kSize, orientation, centre_position, defense_map, attack_grid) {}

    // Remember to override action
    bool action(const Position& target, const std::vector<AttackUnit>& data) override;

    // Constant that defines the size of the ironclad ship
    static constexpr int kSize = 5;
};

/*
Ironclad class: this class represents an ironclad ship of size 5;
this ship can perform an attack on a single enemy cell to reduce the armor of any hit ship by 1.
*/

#endif
