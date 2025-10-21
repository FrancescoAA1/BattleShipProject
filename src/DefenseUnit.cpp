// Author: Enrico Disarò
#include "../include/DefenseUnit.h"

// Default constructor
DefenseUnit::DefenseUnit()
{
    // Initialize the cell as empty
    status_ = DefenseStatus::empty; 

    // Initialize the block's center position as invalid
    center_block_position_ = Position();
    center_block_position_.make_absolute_invalid();

    // Set block size to zero
    full_block_dimension_ = 0;  
}

// Constructor with status and center position
DefenseUnit::DefenseUnit(DefenseStatus status, const Position& center_block_position)
{
    status_ = status; 
    center_block_position_ = center_block_position; 
}

// Setter for status
void DefenseUnit::set_status(DefenseStatus status)
{ 
    status_ = status; 
}

// Setter for block dimension
void DefenseUnit::set_full_block_dimension(int full_block_dimension)
{
    full_block_dimension_ = full_block_dimension; 
}

// Reset the unit to empty state and invalidate center
void DefenseUnit::clear()
{
    status_ = DefenseStatus::empty; 
    center_block_position_.make_absolute_invalid(); 
    full_block_dimension_ = 0; 
}

// Set the center of the block
void DefenseUnit::set_block_center(const Position& position)
{
    center_block_position_.set_x(position.X()); 
    center_block_position_.set_y(position.Y()); 
}

// Two DefenseUnits are equal if they have the same status, block center, and full block dimension
bool operator==(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return (unit1.status() == unit2.status() &&
            unit1.block_center() == unit2.block_center() &&
            unit1.full_block_dimension() == unit2.full_block_dimension()); 
}

// Inequality operator
bool operator!=(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return !(unit1 == unit2); 
}
