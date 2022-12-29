#include "Ship.h"

Ship::Ship(int size, Direction orientation, Position& centre_position, DefenseMap& d_map, AttackMap& a_map)
{
    armor_ = size;
    size_ = size;
    centre_ = centre_position;
    orientation_ = orientation;
    attack_map_ = a_map;
    defense_map_ = d_map;
}

Ship::hit()
{
    armor_--;

    if(armor_ == 0) return true;
    return false;
}