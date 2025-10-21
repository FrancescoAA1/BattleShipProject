// Author: Enrico Disarò
#include "Ship.h"

// Constructor for Ship class
Ship::Ship(int size, Direction orientation, Position& centre_position, DefenseMap& def_map, AttackGrid& att_grid) 
    : attack_grid_(att_grid), defense_map_(def_map)
{
    armor_ = size;                       // set initial armor to ship size
    size_ = size;                        // store ship size
    centre_ = centre_position;            // set center position of the ship
    orientation_ = orientation;           // set ship orientation
    position_ship = std::vector<Position>{}; // initialize ship position vector
}

// Function called when the ship is hit
bool Ship::hit()
{
    armor_--;                             // reduce armor by one

    if (armor_ == 0) return true;         // ship destroyed
    return false;                         // ship still afloat
}
