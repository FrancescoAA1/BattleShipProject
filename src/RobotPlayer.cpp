// Author: Francesco Fantin
#include "../include/RobotPlayer.h"

// The robot invents the move, so the string passed as a parameter will be empty
Move RobotPlayer::get_move(const std::string &move)
{
    Position origin{};
    Position target{};
    Move m;

    int size_list = ship_list.size();
    std::shared_ptr<Ship> ship_cmd;

    // if at least one ship exists in the list, one is randomly selected
    if (size_list > 0)
    {
        ship_cmd = ship_list.at(get_random(ship_list.size()));
    }
    else
    {
        ship_cmd = nullptr;
    }

    // if a ship was selected, that ship will execute the action
    if (ship_cmd)
    {
        // origin position corresponds to the center of the selected ship
        origin = ship_cmd->centre();
        // generate a random target position
        target = get_random_pos();

        int size = ship_cmd->size();

        // distinguish the type of move according to the size of the selected ship
        // NOTE: it would be appropriate to use constants
        if (size == Ironclad::kSize)
        {
            return {origin, target, MoveType::attack};
        }
        else if (size == SupportShip::kSize)
        {
            return {origin, target, MoveType::moveAndFix};
        }
        else
        {
            return {origin, target, MoveType::moveAndDiscover};
        }
    }
    else
    {
        return {origin, target, MoveType::invalid};
    }
}

bool RobotPlayer::add_ships(std::string &cmd, int size)
{
    // generate random positions for bow and stern
    Position bow = get_random_pos();
    // stern position generation is based on bow
    Position stern = get_random_pos(bow, size);

    // check if the ship can be placed on the map
    bool created = defense_map_.add_ship(bow, stern);

    Direction d = get_direction(bow, stern);
    Position p = (bow + stern) / 2;

    // if placement succeeded, call the constructor depending on ship type
    // finally, the newly instantiated ship is added to the ship list
    if (created)
    {
        if (size == Ironclad::kSize)
        {
            std::shared_ptr<Ironclad> ship(new Ironclad{d, p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
        }
        else if (size == SupportShip::kSize)
        {
            std::shared_ptr<SupportShip> ship(new SupportShip{d, p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
        }
        else
        {
            std::shared_ptr<Submarine> ship(new Submarine{p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
        }

        // the command to add the ship is stored in the string passed as a parameter (out)
        cmd = convert_to_command(bow) + " " + convert_to_command(stern);

        return true;
    }
    return false;
}

Position RobotPlayer::get_random_pos()
{
    // generate a random position within the map boundaries
    int x = abs(get_random(defense_map_.kWidth));
    int y = abs(get_random(defense_map_.kHeight));
    return Position(x, y);
}

Position RobotPlayer::get_random_pos(const Position &origin, int size)
{
    if (size > defense_map_.kHeight / 2 + 1)
        return origin;

    bool done = false;
    // x = 0 --> return position with same X and larger Y
    // x = 1 --> return position with same X and smaller Y
    // x = 2 --> return position with same Y and larger X
    // x = 3 --> return position with same Y and smaller X

    // if the randomly obtained position is invalid, keep searching until valid
    while (!done)
    {
        int x = abs(get_random(4));
        if (x == 0)
        {
            int y = origin.Y() + size - 1;
            if (y <= 11)
                return Position(origin.X(), y);
            // if Y exceeds the limit, subtract size
            else
                x = 1;
        }
        else if (x == 1)
        {
            int y = origin.Y() - size + 1;
            if (y >= 0)
                return Position(origin.X(), y);
            // if Y exceeds the limit, add size
            else
                x = 0;
        }
        else if (x == 2)
        {
            int x = origin.X() + size - 1;
            if (x <= 11)
                return Position(x, origin.Y());
            // if X exceeds the limit, subtract size
            else
                x = 3;
        }
        else if (x == 3)
        {
            int x = origin.X() - size + 1;
            if (x >= 0)
                return Position(x, origin.Y());
            // if X exceeds the limit, add size
            else
                x = 2;
        }
        else
            done = true;
    }

    // if we reach this code, an error occurred; return the starting cell
    return origin;
}
