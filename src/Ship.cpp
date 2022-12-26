#include "Ship.h"

Ship::Ship(int size, Direction orientation)
{
    armor_ = size;
    size_ = size;
    orientation_ = orientation;
}

Ship::hit()
{
    armor_--;

    if(armor_ == 0) return true;
    return false;
}