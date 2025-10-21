// Author: Francesco Fantin
#include "../include/DefenseMap.h"

// Default constructor of the class
// Initializes all matrices as empty
DefenseMap::DefenseMap()
{
    // Set the entire defense matrix to empty
    clear_defense_map();
}

// UTILITY FUNCTIONS

// Method that resets the entire defense matrix
void DefenseMap::clear_defense_map()
{
    // Set all cells
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            defense_map_[i][j].clear();
        }
    }
}

// Function that clears all cells in the specified region: center, length, and direction
// Coordinates to clear must already be validated as correct!
void DefenseMap::clear_area(const Position &center_block, int length, Direction orientation)
{
    // Move in the specified direction shifting by length/2
    // Move both "forward" and "backward" according to the direction simultaneously
    Position front;
    Position back;

    // Clear the center first, then the rest
    defense_map_[center_block.Y()][center_block.X()].clear();

    if (orientation == Direction::vertical)
    {
        // swap front and back if inverted
        if (front.Y() < back.Y())
        {
            Position tmp = back;
            back = front;
            front = tmp;
        }
        // create a position representing the offset
        Position offset{0, length / 2};

        while (offset.Y() != 0)
        {
            // Prepare to move forward and backward adding the offset
            front = center_block + offset;
            back = center_block - offset;

            defense_map_[front.Y()][front.X()].clear();
            defense_map_[back.Y()][back.X()].clear();
            // move to the next position along vertical direction
            offset.set_y(offset.Y() - 1);
        }
    }
    else if (orientation == Direction::horizontal)
    {
        if (front.X() < back.X())
        {
            Position tmp = back;
            back = front;
            front = tmp;
        }
        Position offset{length / 2, 0};

        while (offset.X() != 0)
        {
            front = center_block + offset;
            back = center_block - offset;

            defense_map_[front.Y()][front.X()].clear();
            defense_map_[back.Y()][back.X()].clear();

            offset.set_x(offset.X() - 1);
        }
    }
}

// Writes a ship into the matrix
// Init and end must already share the same row or column according to the direction
// Returns true if the operation can be successfully executed
bool DefenseMap::place_ship(Position init, Position end, const Position &new_center_block, const Position &old_center_block, int block_dimension, Direction direction)
{
    if (direction == Direction::horizontal)
    {
        if (check_area_for_placing(new_center_block, old_center_block, std::abs(init.X() - end.X()) + 1, direction) && (std::abs(init.X() - end.X()) + 1 == block_dimension))
        {
            if (init.X() > end.X())
            {
                int tmp = end.X();
                end.set_x(init.X());
                init.set_x(tmp);
            }

            while (init != end)
            {
                defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
                defense_map_[init.Y()][init.X()].set_status(DefenseStatus::taken);
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
                init.set_x(init.X() + 1);
            }
            defense_map_[end.Y()][end.X()].set_block_center(new_center_block);
            defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken);
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
        }
        else
            return false;
    }
    else if (direction == Direction::vertical)
    {
        if (check_area_for_placing(new_center_block, old_center_block, std::abs(init.Y() - end.Y()) + 1, direction) && (std::abs(init.Y() - end.Y()) + 1 == block_dimension))
        {
            if (init.Y() > end.Y())
            {
                int tmp = end.Y();
                end.set_y(init.Y());
                init.set_y(tmp);
            }

            while (init != end)
            {
                defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
                defense_map_[init.Y()][init.X()].set_status(DefenseStatus::taken);
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
                init.set_y(init.Y() + 1);
            }
            defense_map_[end.Y()][end.X()].set_block_center(new_center_block);
            defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken);
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
        }
        else
            return false;
    }
    return true;
}

// Overload of the previous function accepting a vector of positions representing hit status
bool DefenseMap::place_ship(Position init, Position end, const Position &new_center_block, const Position &old_center_block, int block_dimension, Direction direction, const std::vector<DefenseStatus> &relative_hit)
{
    if (relative_hit.size() != block_dimension)
        return false;

    if (direction == Direction::horizontal)
    {
        if (check_area_for_placing(new_center_block, old_center_block, std::abs(init.X() - end.X()) + 1, direction) && (std::abs(init.X() - end.X()) + 1 == block_dimension))
        {
            if (init.X() > end.X())
            {
                int tmp = end.X();
                end.set_x(init.X());
                init.set_x(tmp);
            }
            int x = 0;
            while (init != end)
            {
                defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
                defense_map_[init.Y()][init.X()].set_status(relative_hit.at(x));
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);

                init.set_x(init.X() + 1);
                x++;
            }
            defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
            defense_map_[init.Y()][init.X()].set_status(relative_hit.at(x));
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
        }
        else
            return false;
    }
    else if (direction == Direction::vertical)
    {
        if (check_area_for_placing(new_center_block, old_center_block, std::abs(init.Y() - end.Y()) + 1, direction) && (std::abs(init.Y() - end.Y()) + 1 == block_dimension))
        {
            if (init.Y() > end.Y())
            {
                int tmp = end.Y();
                end.set_y(init.Y());
                init.set_y(tmp);
            }
            int y = 0;
            while (init != end)
            {
                defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
                defense_map_[init.Y()][init.X()].set_status(relative_hit.at(y));
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
                init.set_y(init.Y() + 1);
                y++;
            }
            defense_map_[init.Y()][init.X()].set_block_center(new_center_block);
            defense_map_[init.Y()][init.X()].set_status(relative_hit.at(y));
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
        }
        else
            return false;
    }
    return true;
}

// Check if a position is valid: must remain inside matrix bounds
bool DefenseMap::check_position(const Position &position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.Y() < kHeight);
}

// Check if the center coordinate is a plausible ship position of given length and orientation
bool DefenseMap::check_area_for_placing(const Position &target_destination, const Position &origin_block_center, int length, Direction orientation) const
{
    // Check in the specified direction if any cells are occupied
    Position front = target_destination;
    Position back = target_destination;

    if (orientation == Direction::vertical)
    {
        Position offset{0, length / 2};

        while (offset.Y() != -1)
        {
            front = target_destination + offset;
            back = target_destination - offset;

            if (check_position(front) && check_position(back))
            {
                if (defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty && defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty)
                {
                    offset.set_y(offset.Y() - 1);
                }
                else if (defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty && defense_map_[back.Y()][back.X()].status() != DefenseStatus::empty)
                {
                    if (defense_map_[back.Y()][back.X()].block_center() == origin_block_center)
                        offset.set_y(offset.Y() - 1);
                    else
                        return false;
                }
                else if (defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty && defense_map_[front.Y()][front.X()].status() != DefenseStatus::empty)
                {
                    if (defense_map_[front.Y()][front.X()].block_center() == origin_block_center)
                        offset.set_y(offset.Y() - 1);
                    else
                        return false;
                }
                else
                {
                    if (defense_map_[front.Y()][front.X()].block_center() == origin_block_center && defense_map_[back.Y()][back.X()].block_center() == origin_block_center)
                        offset.set_y(offset.Y() - 1);
                    else
                        return false;
                }
            }
            else
                return false;
        }
    }
    else if (orientation == Direction::horizontal)
    {
        Position offset{length / 2, 0};

        while (offset.X() != -1)
        {
            front = target_destination + offset;
            back = target_destination - offset;

            if (check_position(front) && check_position(back))
            {
                if (defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty && defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty)
                {
                    offset.set_x(offset.X() - 1);
                }
                else if (defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty && defense_map_[back.Y()][back.X()].status() != DefenseStatus::empty)
                {
                    if (defense_map_[back.Y()][back.X()].block_center() == origin_block_center)
                        offset.set_x(offset.X() - 1);
                    else
                        return false;
                }
                else if (defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty && defense_map_[front.Y()][front.X()].status() != DefenseStatus::empty)
                {
                    if (defense_map_[front.Y()][front.X()].block_center() == origin_block_center)
                        offset.set_x(offset.X() - 1);
                    else
                        return false;
                }
                else
                {
                    if (defense_map_[front.Y()][front.X()].block_center() == origin_block_center && defense_map_[back.Y()][back.X()].block_center() == origin_block_center)
                        offset.set_x(offset.X() - 1);
                    else
                        return false;
                }
            }
            else
                return false;
        }
    }
    return true;
}


// DEFENSE FUNCTIONS:

// Returns whether a specific position is free in the defense map
bool DefenseMap::is_free_defense_position(const Position &target_destination) const
{
    return check_position(target_destination) && (defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::empty);
}

// Moves a ship from its current position to the specified target
// target_origin must represent the center of the ship
// Returns true if the movement succeeds
bool DefenseMap::move_ship(const Position &target_origin, const Position &target_destination)
{
    if (!check_position(target_destination) || !check_position(target_origin))
        return false;

    if ((defense_map_[target_origin.Y()][target_origin.X()].status() == DefenseStatus::empty || defense_map_[target_origin.Y()][target_origin.X()].block_center() != target_origin) || 
        (defense_map_[target_destination.Y()][target_destination.X()].status() != DefenseStatus::empty && defense_map_[target_destination.Y()][target_destination.X()].block_center() != target_origin))
        return false;

    int dimension = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension();
    Position offset_o{1, 0};
    Direction direction = Direction::vertical;

    if (check_position(target_origin + offset_o))
    {
        if (defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin)
            direction = Direction::horizontal;
    }

    Position bow;
    Position stern;

    if (direction == Direction::horizontal)
    {
        bow = target_destination + Position{dimension / 2, 0};
        stern = target_destination - Position{dimension / 2, 0};
    }
    else
    {
        bow = target_destination - Position{0, dimension / 2};
        stern = target_destination + Position{0, dimension / 2};
    }

    bool is_on_itself = false;

    if (check_position(bow) && check_position(stern))
    {
        if (defense_map_[bow.Y()][bow.X()].block_center() == target_origin || defense_map_[stern.Y()][stern.X()].block_center() == target_origin)
            is_on_itself = true;
    }

    std::vector<DefenseStatus> units = discover_hitted_blocks(target_origin, direction, dimension);

    if (place_ship(bow, stern, target_destination, target_origin, dimension, direction, units))
    {
        if (is_on_itself)
        {
            Position off = target_destination - target_origin;
            if (off.X() == 0 && off.Y() == 0)
                return true;

            Position end_clear = target_origin;
            Position start_clear = target_destination;

            if (direction == Direction::horizontal)
            {
                if (std::abs((target_origin - bow).X()) < std::abs((target_origin - stern).X()))
                {
                    end_clear.set_x(bow.X() - off.X());
                    start_clear = bow;
                }
                else
                {
                    end_clear.set_x(stern.X() - off.X());
                    start_clear = stern;
                }
                off.X() < 0 ? start_clear.set_x(start_clear.X() + 1) : start_clear.set_x(start_clear.X() - 1);

                while (start_clear != end_clear)
                {
                    defense_map_[start_clear.Y()][start_clear.X()].clear();
                    off.X() < 0 ? start_clear.set_x(start_clear.X() + 1) : start_clear.set_x(start_clear.X() - 1);
                }
                defense_map_[end_clear.Y()][end_clear.X()].clear();
            }
            else
            {
                if (std::abs((target_origin - bow).Y()) < std::abs((target_origin - stern).Y()))
                {
                    end_clear.set_y(bow.Y() - off.Y());
                    start_clear = bow;
                }
                else
                {
                    end_clear.set_y(stern.Y() - off.Y());
                    start_clear = stern;
                }
                off.Y() < 0 ? start_clear.set_y(start_clear.Y() + 1) : start_clear.set_y(start_clear.Y() - 1);

                while (start_clear != end_clear)
                {
                    defense_map_[start_clear.Y()][start_clear.X()].clear();
                    off.Y() < 0 ? start_clear.set_y(start_clear.Y() + 1) : start_clear.set_y(start_clear.Y() - 1);
                }
                defense_map_[end_clear.Y()][end_clear.X()].clear();
            }
        }
        else
            clear_area(target_origin, dimension, direction);

        return true;
    }
    else
        return false;
}

// Fire at a ship in the defense collection
// Returns a pair (center of hit ship, attack result)
// If the shot misses, the center position is invalid
// If the ship is sunk, call remove_ship if you want to remove it from the map
std::pair<Position, AttackUnit> DefenseMap::receive_shot(const Position &target_destination)
{
    Position center_block{};
    if (check_position(target_destination) && defense_map_[target_destination.Y()][target_destination.X()].status() != DefenseStatus::empty)
    {
        if (defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::taken)
        {
            defense_map_[target_destination.Y()][target_destination.X()].set_status(DefenseStatus::hit);
            center_block = defense_map_[target_destination.Y()][target_destination.X()].block_center();
        }
        else
        {
            center_block.make_absolute_invalid();
        }

        return {center_block, AttackUnit::full_and_hit};
    }
    else
        return {center_block, AttackUnit::empty_and_hit};
}

// Remove a ship from the map
bool DefenseMap::remove_ship(const Position &target_origin)
{
    if (check_position(target_origin) && defense_map_[target_origin.Y()][target_origin.X()].block_center() == target_origin)
    {
        int length = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension();

        Position offset_o{1, 0};
        Direction direction = Direction::vertical;

        if (check_position(target_origin + offset_o))
        {
            if (defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin)
                direction = Direction::horizontal;
        }

        clear_area(target_origin, length, direction);
        return true;
    }
    else
        return false;
}

// Get the centers of ships in an area of side length 'side' centered at target_origin
std::vector<Position> DefenseMap::discovers_neighbors(const Position &target_origin, int side) const
{
    std::vector<Position> neighbors_position{};
    if (!check_position(target_origin))
        return neighbors_position;

    Position start = target_origin - Position{side / 2, side / 2};
    Position tmp;

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if (check_position(start))
            {
                if (defense_map_[start.Y()][start.X()].status() != DefenseStatus::empty && defense_map_[start.Y()][start.X()].block_center() != target_origin)
                {
                    tmp = defense_map_[start.Y()][start.X()].block_center();
                    if (std::find(neighbors_position.begin(), neighbors_position.end(), tmp) == neighbors_position.end())
                        neighbors_position.push_back(tmp);
                }
            }
            start.set_x(start.X() + 1);
        }
        start.set_y(start.Y() + 1);
        start.set_x(target_origin.X() - side / 2);
    }
    return neighbors_position;
}

// Repair a ship with the specified center
bool DefenseMap::fix_ship(const Position &target_origin)
{
    if (!check_position(target_origin) || defense_map_[target_origin.Y()][target_origin.X()].block_center() != target_origin)
        return false;

    Position offset_o{1, 0};
    Direction orientation = Direction::vertical;

    if (check_position(target_origin + offset_o))
    {
        if (defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin)
            orientation = Direction::horizontal;
    }

    int size = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension();
    defense_map_[target_origin.Y()][target_origin.X()].set_status(DefenseStatus::taken);

    Position front;
    Position back;

    if (orientation == Direction::vertical)
    {
        Position offset{0, size / 2};
        while (offset.Y() != 0)
        {
            front = target_origin + offset;
            back = target_origin - offset;

            defense_map_[front.Y()][front.X()].set_status(DefenseStatus::taken);
            defense_map_[back.Y()][back.X()].set_status(DefenseStatus::taken);

            offset.set_y(offset.Y() - 1);
        }
    }
    else if (orientation == Direction::horizontal)
    {
        Position offset{size / 2, 0};
        while (offset.X() != 0)
        {
            front = target_origin + offset;
            back = target_origin - offset;

            defense_map_[front.Y()][front.X()].set_status(DefenseStatus::taken);
            defense_map_[back.Y()][back.X()].set_status(DefenseStatus::taken);

            offset.set_x(offset.X() - 1);
        }
    }
    return true;
}

// Discover all ships in a square area of side 'side' centered at target_origin
// Returns a vector representing a dim x dim matrix written row-wise
// If the area exceeds the map, it intersects with the map
// If a ship cell is hit, returns X, otherwise Y
std::vector<AttackUnit> DefenseMap::spot_area(const Position &target_origin, int side) const
{
    std::vector<AttackUnit> discovered_position{};
    if (!check_position(target_origin))
        return discovered_position;

    Position start = target_origin - Position{side / 2, side / 2};

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if (check_position(start))
            {
                if (defense_map_[start.Y()][start.X()].status() == DefenseStatus::empty)
                    discovered_position.push_back(AttackUnit::unknown);
                else if (defense_map_[start.Y()][start.X()].status() == DefenseStatus::taken)
                    discovered_position.push_back(AttackUnit::spotted);
                else
                    discovered_position.push_back(AttackUnit::full_and_hit);
            }
            start.set_x(start.X() + 1);
        }
        start.set_y(start.Y() + 1);
        start.set_x(target_origin.X() - side / 2);
    }

    return discovered_position;
}

// Returns whether there are blocks with the specified center
bool DefenseMap::center_block_discovery(const Position &center_block) const
{
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (defense_map_[i][j].block_center() == center_block)
                return true;
        }
    }
    return false;
}

// Adds a ship to the map
// bow_position is the bow, stern_position is the stern
// Returns true if successfully added, false if a ship with the same center exists
bool DefenseMap::add_ship(const Position &bow_position, const Position &stern_position)
{
    if ((!check_position(bow_position) || !check_position(stern_position)) || (bow_position.X() != stern_position.X() && bow_position.Y() != stern_position.Y()))
        return false;

    Position center_block = (bow_position + stern_position) / 2;

    if (center_block_discovery(center_block))
        return false;

    int size;
    Direction orientation = Direction::vertical;

    if (bow_position.Y() == stern_position.Y())
    {
        orientation = Direction::horizontal;
        size = std::abs(bow_position.X() - stern_position.X()) + 1;
    }
    else
        size = std::abs(bow_position.Y() - stern_position.Y()) + 1;

    if (size != kShipType1Dim && size != kShipType2Dim && size != kShipType3Dim)
        return false;

    Position init = bow_position;
    Position end = stern_position;

    return place_ship(init, end, center_block, center_block, size, orientation);
}

// Converts the defense map to a string representation
std::string DefenseMap::to_string() const
{
    std::string result = ">  ";
    char row_index = kFirstRowLetter;
    int column_index = kFirstColumnNumber;

    for (int i = 0; i < kWidth; i++)
    {
        result += std::to_string(column_index);
        result += " ";
        if (i < 9)
            result += " ";
        column_index++;
    }
    result += "\n";

    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (j == 0)
            {
                if (row_index >= 'J')
                {
                    row_index = row_index + 2;
                    result.append(1, row_index);
                    row_index = row_index - 2;
                }
                else
                    result.append(1, row_index);

                result += "  ";
                row_index++;
            }

            switch (defense_map_[i][j].status())
            {
            case DefenseStatus::empty:
                result += "   ";
                break;
            case DefenseStatus::hit:
                switch (defense_map_[i][j].full_block_dimension())
                {
                case kShipType1Dim:
                    result += kSubmarineUnitHit;
                    result += "  ";
                    break;
                case kShipType2Dim:
                    result += kSupportShipUnitHit;
                    result += "  ";
                    break;
                case kShipType3Dim:
                    result += kIroncladUnitHit;
                    result += "  ";
                    break;
                }
                break;
            case DefenseStatus::taken:
                switch (defense_map_[i][j].full_block_dimension())
                {
                case kShipType1Dim:
                    result += kSubmarineUnit;
                    result += "  ";
                    break;
                case kShipType2Dim:
                    result += kSupportShipUnit;
                    result += "  ";
                    break;
                case kShipType3Dim:
                    result += kIroncladUnit;
                    result += "  ";
                    break;
                }
                break;
            }
        }
        result += "\n";
    }

    return result;
}

// Overload of << operator to print the defense map
std::ostream &operator<<(std::ostream &data_stream, const DefenseMap &defense_map)
{
    return data_stream << defense_map.to_string();
}

// Returns a vector of block states representing whether the ship’s block has been hit
std::vector<DefenseStatus> DefenseMap::discover_hitted_blocks(const Position &center, Direction direction, int size)
{
    if (!check_position(center) || defense_map_[center.Y()][center.X()].block_center() != center || defense_map_[center.Y()][center.X()].full_block_dimension() != size)
        return std::vector<DefenseStatus>{};

    std::vector<DefenseStatus> units{};

    if (direction == Direction::horizontal)
    {
        Position off_x{size / 2, 0};
        Position init = center - off_x;
        Position end = center + off_x;

        while (init != end)
        {
            units.push_back(defense_map_[init.Y()][init.X()].status());
            init.set_x(init.X() + 1);
        }
        units.push_back(defense_map_[init.Y()][init.X()].status());
    }

    if (direction == Direction::vertical)
    {
        Position off_y{0, size / 2};
        Position init = center - off_y;
        Position end = center + off_y;

        while (init != end)
        {
            units.push_back(defense_map_[init.Y()][init.X()].status());
            init.set_y(init.Y() + 1);
        }
        units.push_back(defense_map_[init.Y()][init.X()].status());
    }

    return units;
}
