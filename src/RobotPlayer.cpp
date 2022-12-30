#include "../include/RobotPlayer.h"

// il robot inventa la mossa per cui la stringa passata come parametro sarà vuota
Move RobotPlayer::get_move(const std::string &move)
{
    Ship *ship_cmd = ship_list.at(get_random_index(ship_list.size()));
    Position origin{};
    Position target{};
    Move m;

    if (ship_cmd)
    {
        // posizione di origine corrisponde al centro della nave appena ottenuta
        origin = ship_cmd->centre();
        // viene generato una posizione target casuale
        target = get_random_pos();

        int size = ship_cmd->size();

        // distinzione del tipo di mossa a seconda della taglia della nave restituita
        // NOTA: sarebbe opportuno usare delle costanti
        if (size == 5)
        {
            m = {origin, target, MoveType::attack};
            current_move = m;
            return m;
        }
        else if (size == 3)
        {
            m = {origin, target, MoveType::moveAndFix};
            current_move = m;
            return m;
        }
        else
        {
            m = {origin, target, MoveType::moveAndDiscover};
            current_move = m;
            return m;
        }
    }
    else
    {
        m = {origin, target, MoveType::invalid};
        current_move = m;
        return m;
    }
}

int RobotPlayer::get_random_index(int size)
{
    return std::rand() % size;
}

Position &RobotPlayer::get_random_pos()
{
    int x = std::rand() % 12;
    int y = std::rand() % 12;
    Position target{x, y};
    return target;
}

bool RobotPlayer::add_ships(const std::string& cmd)
{
    Position origin = get_random_pos();
    
    return true;
}