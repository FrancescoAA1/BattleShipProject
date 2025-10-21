// Author: Francesco Fantin
#include "../include/HumanPlayer.h"

Move HumanPlayer::get_move(const std::string &cmd)
{
    // create two positions using the default constructor
    Position origin{};
    Position target{};
    Move m;

    // before splitting the string into two coordinates
    // check if the string corresponds to a command to display both maps
    // or a command to clear the map
    if (cmd == "XX XX")
    {
        m.set_movetype(MoveType::showMap);
        return m;
    }
    else if (cmd == "AA AA")
    {
        m.set_movetype(MoveType::clearSonared);
        return m;
    }
    else if (cmd == "BB BB")
    {
        m.set_movetype(MoveType::clearFullHit);
        return m;
    }
    else if (cmd == "CC CC")
    {
        m.set_movetype(MoveType::clearEmptyHit);
        return m;
    }
    else
    {
        // split the string into two parts (delimiter is a space)
        int pos = cmd.find_first_of(' ');

        try
        {
            std::string first_pair = cmd.substr(0, pos);
            std::string second_pair = cmd.substr(pos + 1);

            // convert each coordinate pair into a Position
            origin = convert_to_position(first_pair);
            target = convert_to_position(second_pair);
        }
        catch (std::out_of_range &ex)
        {
            return {origin, target, MoveType::invalid};
        }

        if (origin.is_absolute_invalid() || target.is_absolute_invalid())
            return {origin, target, MoveType::invalid};

        // find the ship that will perform the action
        std::shared_ptr<Ship> ship_cmd = get_ship(origin);

        if (ship_cmd)
        {
            // distinguish the move type according to the ship size
            // NOTE: using constants would be better
            int size = ship_cmd->size();

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
}

bool HumanPlayer::add_ships(std::string &cmd, int size)
{
    Position bow{};
    Position stern{};

    // split the string into two parts (delimiter is a space)
    int pos = cmd.find_first_of(' ');

    try
    {
        std::string first_pair = cmd.substr(0, pos);
        std::string second_pair = cmd.substr(pos + 1);

        // convert each coordinate pair into a Position
        bow = convert_to_position(first_pair);
        stern = convert_to_position(second_pair);
    }
    catch (std::out_of_range &ex)
    {
        return false;
    }

    // check that both positions are valid
    if (!(bow.is_absolute_invalid() || stern.is_absolute_invalid()))
    {
        // check that the size of the ship to place
        // matches the size deducible from the coordinates provided
        int c_size = get_size(bow, stern);
        if (c_size == size)
        {
            if (defense_map_.add_ship(bow, stern))
            {
                Direction d = get_direction(bow, stern);
                Position p = (bow + stern) / 2;

                // distinguish the ship type based on size
                // add the ship pointer to the ship vector
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
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
