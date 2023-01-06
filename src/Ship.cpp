#include "Ship.h"
#include <iostream>

Ship::Ship(int size, Direction orientation, Position& centre_position, DefenseMap& def_map, AttackGrid& att_grid) : attack_grid_(att_grid), defense_map_(def_map)
{
    armor_ = size;
    size_ = size;
    centre_ = centre_position;
    orientation_ = orientation;
    attack_grid_ = att_grid;
    defense_map_ = def_map;
}

bool Ship::hit()
{
    armor_--;
    std::cout << "Armatura " << std::to_string(armor()); 

    if(armor_ == 0) return true;
    return false;
}