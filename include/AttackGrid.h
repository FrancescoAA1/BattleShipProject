// Author: Mattia Galassi 
#ifndef BATTLESHIPPROJECT_ATTACKGRID_H_
#define BATTLESHIPPROJECT_ATTACKGRID_H_

// Class representing the attack map
// It contains a matrix of attack units and methods to check
// the status of requested positions

#include "AttackUnit.h"
#include "Position.h"
#include <vector>
#include <ostream>
#include <string>

class AttackGrid
{
public:
    // Dimension constants can be public and accessible from outside
    static constexpr int kHeight = 12;
    static constexpr int kWidth = 12;

    // Default constructor that sets all cells to empty
    AttackGrid();

    // ATTACK functions:

    // Function that sets the selected position as spotted
    // Updates the attack map
    // Returns true if spotting was successful
    // Spotting fails if the cell is not empty or invalid
    bool spot_position(const Position &target_destination);

    // Sets the specified cell of the attack map to the value passed as a parameter (shot_status)
    // Returns true if the shot was successful
    // Fails if the cell is not empty or invalid
    bool shot_position(const Position &target_destination, AttackUnit shot_status);

    // Utility functions

    // Function that clears all cells in the matrix
    void clear_area();

    // Function that clears all cells marked as X in the matrix
    void clear_all_full_and_hit();

    // Function that clears all cells marked as O in the matrix
    void clear_all_full_and_empty();

    // Function that clears all cells marked as Y in the matrix
    void clear_sonared();

    // Function that converts the attack map to a string
    std::string to_string() const;

    // Checks if a given position is valid (must be within the matrix bounds)
    bool check_position(const Position &position) const;

private:
    // Region of constants to use in the class
    static constexpr char kHitAndFullSymbol = 'X';
    static constexpr char kHitAndEmptySymbol = 'O';
    static constexpr char kSpottedSymbol = 'Y';
    static constexpr char kEmptySpace = ' ';
    static constexpr char kFirstRowLetter = 'A';
    static constexpr int kFirstColumnNumber = 1;

    // Represents the attack map to use
    AttackUnit attack_grid_[kHeight][kWidth];

    // ATTACK GRID: a class that represents an attack map and provides methods 
    // to locate and update the status of cells. Used by ships for attack and 
    // discovery functions of the submarine.
};

// Overload of the << operator to print the attack map
std::ostream &operator<<(std::ostream &data_stream, const AttackGrid &attack_grid);

#endif
