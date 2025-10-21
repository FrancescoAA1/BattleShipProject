// Author: Enrico Disarò
#include "Submarine.h"

// To perform its movement and inspection action, the submarine needs the following data:
// The target position of the movement, which is also the center of the inspected area
// A vector of AttackUnit, which contains the portion of the enemy map that has been inspected
//
// The checks on the validity of the move have already been performed, 
// and the ship can therefore safely proceed with the action

bool Submarine::action(const Position &target, const std::vector<AttackUnit> &data)
{
    if (data.empty())
    {
        return false;
    }

    bool allowed = defense_map_.move_ship(this->centre(), target);

    // move the submarine
    if (allowed)
    {
        // move the center of the ship
        set_center(target);

        int counter = 0;

        for (int y = -kSide / 2; y <= kSide / 2; y++)
        {
            for (int x = -kSide / 2; x <= kSide / 2; x++)
            {
                // check if the relative position in the array with respect to the center is valid, 
                // and if it is, proceed to check the content of the vector; otherwise skip and continue
                Position t = Position(target.X() + x, target.Y() + y);
                if (this->attack_grid_.check_position(t))
                {
                    if (data[counter] == AttackUnit::spotted)
                        attack_grid_.spot_position(t);
                    counter++;
                }
            }
        }

        return true;
    }

    // if we get here, it means the movement was not allowed
    return false;
}
