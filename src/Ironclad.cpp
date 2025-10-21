// Author: Enrico Disarò
#include "Ironclad.h"

// To perform its attack action, the Ironclad ship requires the following data:
// The attack map of the player issuing the move, which will be modified
// The target position of the attack
// The new AttackUnit to replace in the received attack map at the target position
// Although only one AttackUnit is received, an array is used to conform to the action methods of all ships
//
// Validity checks for the move have already been performed, so the ship can safely execute the action
// Returns a boolean confirming whether the action was performed

bool Ironclad::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() > 0)
    {
        bool b = attack_grid_.shot_position(target, data[0]);
        return b;
    }
    else 
    {
        return false;
    }
}
