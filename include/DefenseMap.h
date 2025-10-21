// Author: Mattia Galassi
#ifndef BATTLESHIPPROJECT_DEFENSEMAP_H_
#define BATTLESHIPPROJECT_DEFENSEMAP_H_

#include "Position.h"
#include "DefenseUnit.h"
#include "AttackUnit.h"
#include "Direction.h"
#include <ostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>

class DefenseMap
{
public:
    // The constants for dimensions can be public and accessible externally
    static constexpr int kHeight = 12;
    static constexpr int kWidth = 12;

    // Default constructor
    // Initializes all matrices as empty
    DefenseMap();

    // DEFENSE FUNCTIONS:

    // Returns whether a given position is free in the defense map
    bool is_free_defense_position(const Position &target_destination) const;

    // Moves a ship from its current position to the specified target
    // The origin position must represent the center of the ship to move
    // The second parameter is the target destination
    // Returns true if the move was successful
    bool move_ship(const Position &target_origin, const Position &target_destination);

    // Shoots at a ship in my collection because it has been hit
    // Returns a pair (center position of the hit ship, attack status)
    // If the shot misses, it returns O and an invalid center position
    // If the ship is sunk, call remove_ship if you want to remove it from the map
    std::pair<Position, AttackUnit> receive_shot(const Position &target_destination);

    // Function to remove a ship from the map
    bool remove_ship(const Position &target_origin);

    // Function to get the centers of ships in a specified square area with side 'side' centered on
    // the given target_origin
    // If the area extends outside the matrix, it intersects it. If the area is larger than the matrix
    // and contains it => returns all centers in the matrix
    std::vector<Position> discovers_neighbors(const Position &target_origin, int side) const;

    // Function that repairs the ship with the center specified in target_origin
    bool fix_ship(const Position &target_origin);

    // Function that spots all ships in an area dim x dim starting from the center specified as target
    // Returns an area representing a dim x dim matrix written row by row
    // The integer specifies the side length for the area
    // If the area does not fit in the matrix, it intersects it
    // If the area contains the matrix, returns the whole matrix
    // If the ship has a hit cell, returns X, otherwise Y
    std::vector<AttackUnit> spot_area(const Position &target_origin, int side) const;

    // OTHER UTILITY FUNCTIONS

    // Function to add a ship
    // The first parameter is the bow position and the second is the stern position
    // Returns true if the operation was successful, false if it was already present
    bool add_ship(const Position &bow_position, const Position &stern_position);

    // Function that writes the map to a string
    std::string to_string() const;

    // Checks if a given position is valid (must fit within matrix dimensions)
    bool check_position(const Position &position) const;

private:
    // Region for constants used in the class
    static constexpr char kEmptySpace = ' ';
    static constexpr char kIroncladUnitHit = 'c';
    static constexpr char kIroncladUnit = 'C';
    static constexpr char kSubmarineUnitHit = 'e';
    static constexpr char kSubmarineUnit = 'E';
    static constexpr char kSupportShipUnitHit = 's';
    static constexpr char kSupportShipUnit = 'S';
    static constexpr char kFirstRowLetter = 'A';
    static constexpr int kFirstColumnNumber = 1;
    static constexpr int kShipType1Dim = 1;
    static constexpr int kShipType2Dim = 3;
    static constexpr int kShipType3Dim = 5;

    // Represents the map used for defense
    DefenseUnit defense_map_[kHeight][kWidth];

    // Writes a ship into the matrix
    // Start and end must already share the same row or column according to the direction
    // Returns true if the operation is executable correctly
    // Init and end are passed by value because they will be modified internally
    bool place_ship(Position init, Position end, const Position &new_center_block, const Position &old_center_block, int block_dimension, Direction direction);

    // Overload of the previous function that accepts a vector of DefenseStatus representing ship cells
    // to be marked as hit (useful for moving ships)
    bool place_ship(Position init, Position end, const Position &new_center_block, const Position &old_center_block, int block_dimension, Direction direction, const std::vector<DefenseStatus>& relative_hit);

    // Returns a vector of states representing whether the relative block in the ship is hit or not
    std::vector<DefenseStatus> discover_hitted_blocks(const Position& center, Direction direction, int size); 

    // Checks if the specified center coordinate is a plausible position for a ship of given length and orientation
    // Returns true if the ship would cover a non-empty area or goes out of the matrix
    bool check_area_for_placing(const Position &target_destination, const Position &origin_block_center, int length, Direction orientation) const;

    // Function that clears all cells in the specified region: center, length, and direction
    // The coordinates to clear must already be tested as correct!
    void clear_area(const Position &center_block, int length, Direction orientation);

    // Method that resets the entire defense matrix
    void clear_defense_map();

    // Function that returns whether there are blocks with a center equal to the target
    bool center_block_discovery(const Position &center_block) const;
};

// Overload of the << operator to write the defense matrix to an output stream
std::ostream &operator<<(std::ostream &data_stream, const DefenseMap &defense_map);

#endif
