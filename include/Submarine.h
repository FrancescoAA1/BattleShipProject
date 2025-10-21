// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_SUBMARINE_H_
#define BATTLESHIPPROJECT_SUBMARINE_H_

#include "Ship.h"
#include "Utility.h"

class Submarine : public Ship
{
public:
    // Constructor
    // Creates a ship with armor = 1, size = 1
    // No need to provide orientation since length is 1 and it would be irrelevant
    // Orientation will still be set to a default value for completeness
    Submarine(Position& centre_position, DefenseMap& defense_map, AttackGrid& attack_grid) 
        : Ship(kSize, kDefaultDirection, centre_position, defense_map, attack_grid) {}

    // Remember to override action
    bool action(const Position& target, const std::vector<AttackUnit>& data) override;

    // Constant defining the size of the submarine
    static constexpr int kSize = 1;

private:

    // Constant defining the default orientation of the submarine
    static constexpr Direction kDefaultDirection = Direction::horizontal;
    // Constant defining the side length of the inspected map area
    // The inspected area is a square and the side length is odd to allow the ship to be in the center
    static constexpr int kSide = 5;
}; 

/*
Class Submarine: represents a submarine;
This ship has size 1, and can perform a move + inspection operation in the area it moves to,
covering a 5x5 square (inspection = marks enemy ships on the player's attack map with a Y)
*/

#endif
