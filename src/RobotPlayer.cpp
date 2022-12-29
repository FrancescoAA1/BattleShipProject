#include "../include/RobotPlayer.h"

// il robot inventa la mossa per cui la stringa passata come parametro sarà vuota
Move RobotPlayer::get_move(const std::string &move)
{
    Ship *ship_cmd = ship_list.at(get_random_index(ship_list.size()));
    Position origin{};
    Position target{};

    if (ship_cmd)
    {
        // posizione di origine corrisponde al centro della nave appena ottenuta
        origin = ship_cmd->centre();
        //viene generato una posizione target casuale
        target = get_random_pos();

        int size = ship_cmd->size();

        //distinzione del tipo di mossa a seconda della taglia della nave restituita
        //NOTA: sarebbe opportuno usare delle costanti
        if (size == 5)
        {
            return {origin, target, MoveType::attack};
        }
        else if (size == 3)
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

int RobotPlayer::get_random_index(int size)
{
    return std::rand() % size;
}

Position& RobotPlayer::get_random_pos()
{
    int x = std::rand() % 12;
    int y = std::rand() % 12;
    Position target{x, y};
    return target;
}