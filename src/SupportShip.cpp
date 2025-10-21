// Author: Enrico Disarò
#include "SupportShip.h"

// To perform its movement and repair action, the support ship needs the following data:
// The target position of the movement, which is also the center of the repair area.
// Even though the ship does not require attack units provided by others to perform its action,
// an (empty) array is still passed in order to make the action methods of all ships consistent.
//
// The checks on the validity of the move have already been performed, 
// and the ship can therefore safely proceed with the action.
// A boolean value is still returned to confirm that the move was executed.

bool SupportShip::action(const Position &target, const std::vector<AttackUnit> &data)
{
    if (defense_map_.move_ship(this->centre(), target))
    {
        position_ship = defense_map_.discovers_neighbors(target, kSide);

        for (int i = 0; i < position_ship.size(); i++)
        {
            // repair the ship, and if the action is not valid, return false
            if (!defense_map_.fix_ship(position_ship[i]))
            {
                return false;
            }
        }

        // move the center of the ship
        set_center(target);
        return true;
    }

    // if we get here, it means the movement was not valid
    return false;
}
