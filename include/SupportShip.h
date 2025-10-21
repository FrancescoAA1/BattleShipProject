// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_SUPPORTSHIP_H_
#define BATTLESHIPPROJECT_SUPPORTSHIP_H_

#include "Ship.h"
#include "Utility.h"
#include <ostream>

class SupportShip : public Ship
{
public:
    // Constructor
    // Creates a ship with armor = 3, size = 3, and given orientation
    SupportShip(Direction orientation, Position &centre_position, DefenseMap &def_map, AttackGrid &att_grid) 
        : Ship(kSize, orientation, centre_position, def_map, att_grid) {}

    // Remember to override action
    bool action(const Position &target, const std::vector<AttackUnit> &data) override;

    // Constant defining the size of the support ship
    static constexpr int kSize = 3;

private:
    // Constant defining the side length of the healing area
    // The healing area is a square and the side length is odd to allow the ship to be at the center of the area
    static constexpr int kSide = 3;
};

/*
Class SupportShip: represents the support ship of size 3;
This ship can perform the move + heal operation for allied ships in a 3x3 area.
*/

#endif
