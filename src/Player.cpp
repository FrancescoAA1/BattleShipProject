// Author: Francesco Fantin
#include "../include/Player.h"

Player::Player(const std::string &nickname)
{
    nickname_ = nickname;
    attack_grid_ = AttackGrid();
    defense_map_ = DefenseMap();
    // the ship vector is initially empty because ships are added with push_back
    ship_list = std::vector<std::shared_ptr<Ship>>(0);
}

std::shared_ptr<Ship> Player::get_ship(const Position origin)
{
    // search for the pointer to the ship whose center matches the origin position
    auto it = std::find_if(ship_list.begin(), ship_list.end(), [origin](std::shared_ptr<Ship> ship) -> bool
                           { return (ship->centre() == origin); });

    // if the iterator returned by the STL algorithm points to the end of the vector,
    // the ship was not found and nullptr is returned, otherwise the ship pointer is returned
    if (it != ship_list.end())
    {
        return *it;
    }
    else
    {
        return nullptr;
    }
}

std::vector<AttackUnit> Player::retrieve_unit(const Position &target)
{
    // the opposing player returns a vector of AttackUnit indicating
    // the ships present in the 5x5 area centered on the given position
    std::vector<AttackUnit> att = defense_map_.spot_area(target, 5);
    return att;
}

AttackUnit Player::receive_attack(const Position &target)
{
    // the player's map receiving the enemy attack is updated
    std::pair<Position, AttackUnit> shot_info = defense_map_.receive_shot(target);
    // position to analyze
    Position p = shot_info.first;

    // check if the position is valid
    if (!p.is_absolute_invalid())
    {
        // check if a ship is present at the position returned by receive_shot
        std::shared_ptr<Ship> ship_attacked = get_ship(p);

        if (ship_attacked)
        {
            bool sunk = ship_attacked->hit();

            // if the ship was sunk, remove it from the ship list and map
            if (sunk)
            {
                ship_list.erase(std::remove(ship_list.begin(), ship_list.end(), ship_attacked), ship_list.end());
                defense_map_.remove_ship(p);
            }
        }
    }
    // the opposing player returns the state of the just-hit cell
    return shot_info.second;
}

std::vector<AttackUnit> Player::execute_move(const Position &target, const MoveType &type)
{
    std::vector<AttackUnit> units;

    // if the move is performed by a battleship
    if (type == MoveType::attack)
    {
        units = {receive_attack(target)};
    }
    // if the move is performed by a sonar
    else if (type == MoveType::moveAndDiscover)
    {
        units = {retrieve_unit(target)};
    }

    // in the case of a move performed by a support ship, the AttackUnit vector
    // is correctly empty, because the move does not affect the opposing player
    return units;
}

bool Player::handle_response(std::vector<AttackUnit> units, const Move &m)
{
    // find the ship assigned to perform the action
    std::shared_ptr<Ship> ship = get_ship(m.origin());
    // execute the action on the assigned ship
    bool action_done = ship->action(m.target(), units);

    // if the action is performed by a support ship, repair the armor of all surrounding ships
    if (action_done && m.movetype() == MoveType::moveAndFix)
    {
        // vector of ship centers
        std::vector<Position> last_fixed_ships = ship->get_position_ships();

        for (int i = 0; i < last_fixed_ships.size(); i++)
        {
            // repair each ship
            this->get_ship(last_fixed_ships[i])->restore();
        }
    }

    return action_done;
}

// provides the direction of the ship to place
Direction get_direction(const Position &bow, const Position &stern)
{
    if (bow.X() == stern.X())
    {
        return Direction::vertical;
    }
    return Direction::horizontal;
}

// provides the size of the ship to place
int get_size(const Position &bow, const Position &stern)
{
    Direction placing = get_direction(bow, stern);

    if (placing == Direction::horizontal)
    {
        return abs(bow.X() - stern.X()) + 1;
    }
    else
        return abs(bow.Y() - stern.Y()) + 1;
}

Player::~Player()
{
    std::shared_ptr<Ship> pointer;
    // deallocate all ships
    for (int i = 0; i < ship_list.size(); i++)
    {
        pointer = ship_list[i];
        // delete pointer;  // shared_ptr automatically manages memory
    }

    pointer = nullptr;
}
