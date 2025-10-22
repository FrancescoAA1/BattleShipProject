// Author: Francesco Fantin
#include "../include/AttackGrid.h"

// Default constructor that sets all cells to empty
AttackGrid::AttackGrid()
{
    clear_area();
}

// Function that sets the specified position as spotted
// Updates the attack map
// Returns true if spotting was successful
// Spotting fails if the cell is invalid
bool AttackGrid::spot_position(const Position &target_destination)
{
    // If the position is valid, update the attack map
    if (check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = AttackUnit::spotted;
        return true;
    }
    else
        return false;
}

// Sets a cell of the attack map as hit for the specified target
// Updates the attack map
// Returns true if the shot was successful
// The shot fails if the cell is invalid
bool AttackGrid::shot_position(const Position &target_destination, AttackUnit shot_status)
{
    // If the position is valid, update the attack map
    if (check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = shot_status;
        return true;
    }
    else
        return false;
}

// Function that clears all cells in the attack matrix
void AttackGrid::clear_area()
{
    // Set all cells to unknown
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            attack_grid_[i][j] = AttackUnit::unknown;
        }
    }
}

// Checks if a given position is valid (within matrix bounds)
bool AttackGrid::check_position(const Position &position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.Y() < kHeight);
}

// Function that converts the attack map to a string representation
std::string AttackGrid::to_string() const
{
    std::string result = ">  ";
    // Read all cells and write them to the resulting string
    // Use their corresponding symbol representation
    // Add row letters and column numbers for coordinates
    char row_index = kFirstRowLetter;
    int column_index = kFirstColumnNumber;

    for (int i = 0; i < kWidth; i++)
    {
        result += std::to_string(column_index);
        result += " ";
        if (i < 9)
        {
            result += " ";
        }
        column_index++;
    }
    result += "\n";

    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            // Write the row letter
            if (j == 0)
            {
                if (row_index >= 'J')
                {
                    row_index = row_index + 2;
                    result.append(1, row_index);
                    row_index = row_index - 2;
                }
                else
                {
                    result.append(1, row_index);
                }
                result += "  ";

                row_index++;
            }
            switch (attack_grid_[i][j])
            {
            case AttackUnit::unknown:
                result += "   ";
                break;
            case AttackUnit::empty_and_hit:
                result += kHitAndEmptySymbol;
                result += "  ";
                break;
            case AttackUnit::full_and_hit:
                result += kHitAndFullSymbol;
                result += "  ";
                break;
            case AttackUnit::spotted:
                result += kSpottedSymbol;
                result += "  ";
                break;
            }
        }
        result += "\n";
    }

    return result;
}

// Overload of the << operator to print the attack map
std::ostream &operator<<(std::ostream &data_stream, const AttackGrid &attack_grid)
{
    return data_stream << attack_grid.to_string();
}

// Function that clears all cells marked as 'X' in the matrix
void AttackGrid::clear_all_full_and_hit()
{
    // Set all cells marked with 'X' to unknown
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::full_and_hit)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}

// Function that clears all cells marked as 'O' in the matrix
void AttackGrid::clear_all_full_and_empty()
{
    // Set all cells marked with 'O' to unknown
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::empty_and_hit)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}

// Function that clears all cells marked as 'Y' in the matrix
void AttackGrid::clear_sonared()
{
    // Set all cells marked with 'Y' to unknown
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::spotted)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}
