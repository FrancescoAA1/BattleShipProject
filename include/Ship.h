// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_SHIP_H_
#define BATTLESHIPPROJECT_SHIP_H_

#include <vector>
#include "Position.h"
#include "AttackUnit.h"
#include "Direction.h"
#include "AttackGrid.h"
#include "DefenseMap.h"

class Ship
{
public:
    // Disable copy constructor to make the class abstract
    Ship(const Ship &) = delete;
    // Disable copy assignment to make the class abstract
    Ship &operator=(const Ship &) = delete;

    // Virtual method defining the action the ship can perform (attack, move and heal, move and inspect)
    // Must be implemented differently in each derived ship class
    // The vector of AttackUnit represents a set of attack units provided by the defending player to the attacking player
    // It contains updated attack units to replace in the attacker’s attack map
    // In the case of healing, the vector will be empty
    // In the case of an attack, the vector will contain only one unit
    // In the case of inspection, the vector will contain 25 units
    // A boolean is returned to confirm the success of the move
    virtual bool action(const Position &target, const std::vector<AttackUnit> &) = 0;

    // Getter methods
    int armor() const { return armor_; }
    int size() const { return size_; }
    Position centre() const { return centre_; }
    std::vector<Position> get_position_ships() { return position_ship; };
    Direction orientation() const { return orientation_; }
    AttackGrid attack_grid() const { return attack_grid_; }
    DefenseMap defense_map() const { return defense_map_; }

    // Setter methods
    void set_center(const Position &new_centre) { centre_ = new_centre; }

    // The ship has been hit: reduces armor by 1
    // Returns true if the ship has just been sunk (used to notify removal from the dictionary)
    bool hit();
    // The ship has been healed by a support ship: restores armor to its initial value (size_)
    void restore() { armor_ = size_; };

    virtual ~Ship(){};

protected:
    // Constructor requires ship size, orientation, center, and the maps it belongs to
    Ship(int, Direction, Position &, DefenseMap &, AttackGrid &);

    // Reference to the attack map this ship is part of
    AttackGrid &attack_grid_;
    // Reference to the defense map this ship is part of
    DefenseMap &defense_map_;

    // Vector containing information about positions of neighboring ship centers
    std::vector<Position> position_ship;

private:
    // Variable defining the direction the ship is oriented
    Direction orientation_;
    // Variable indicating the current armor of the ship
    int armor_;
    // Variable defining the size of the ship
    int size_;
    // Variable indicating the center of the ship
    Position centre_;
};

/*
Class Ship: represents a generic ship available to the player
This class is abstract, with 3 derived subclasses, one for each type of ship in the game
The core feature of this class is the action() method
*/

#endif
