// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_DEFENSEUNIT_H_
#define BATTLESHIPPROJECT_DEFENSEUNIT_H_

#include "Position.h"

// Represents the state of a cell on the map
// if empty => there is no ship on it
// if hit => the ship present on it has been hit
// if taken => the position is occupied by a ship
enum DefenseStatus
{
    empty,
    hit,
    taken
}; 

class DefenseUnit
{
public: 
    // Default constructor sets the reference center position as invalid
    // and the status to empty
    DefenseUnit(); 

    // Constructor with specified parameters
    DefenseUnit(DefenseStatus status, const Position& center_block_position); 

    // Get the status of the cell
    DefenseStatus status() const { return status_; }

    // Set the cell status to a value from the enumerator
    void set_status(DefenseStatus status);

    // Clear the cell: set status to empty and center to an invalid position
    void clear(); 

    // Get the center of the reference block
    Position block_center() const { return center_block_position_; }

    // Set the reference center to a specific value
    void set_block_center(const Position& position);  

    // Get the dimension of the block to which it belongs
    int full_block_dimension() const { return full_block_dimension_; } 

    // Set the dimension value of the block to which it belongs
    void set_full_block_dimension(int full_block_dimension); 

private: 
    DefenseStatus status_; 
    Position center_block_position_;
    int full_block_dimension_; 
}; 

// Overload equality operators for the class defined above
bool operator==(const DefenseUnit&, const DefenseUnit&); 
bool operator!=(const DefenseUnit&, const DefenseUnit&); 

/*
Class DefenseUnit: represents a unit on the game field.
It has a status that allows checking whether that particular cell
represents a position occupied by a ship or a hit zone of a ship.
Each unit maintains a reference to the center of the overall block 
it belongs to, to make map operations more efficient and reduce 
representation complexity. 
Additionally, a DefenseUnit has an integer specifying the dimension 
of the block it belongs to, again to facilitate writing operations.
*/
#endif
