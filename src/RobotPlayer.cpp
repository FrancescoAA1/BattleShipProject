#include "../include/RobotPlayer.h"

// il robot inventa la mossa per cui la stringa passata come parametro sarà vuota
Move RobotPlayer::get_move(const std::string &move)
{
    Ship *ship_cmd = ship_list.at(get_random_index(ship_list.size()));

    if (ship_cmd)
    {
        // posizione di origine corrisponde al centro della nave appena ottenuta
        Position origin = ship_cmd->centre();
        //viene generato una posizione target casuale
        Position target = get_random_pos();

        int size = ship_cmd->size();

        //distinzione del tipo di mossa a seconda della taglia della nave restituita
        //NOTA: sarebbe opportuno usare delle costanti
        if (size == 5)
        {
            Move m{origin, target, MoveType::attack};
            return m;
        }
        else if (size == 3)
        {
            Move m{origin, target, MoveType::moveAndFix};
            return m;
        }
        else
        {
            Move m{origin, target, MoveType::moveAndDiscover};
            return m;
        }
    }
    else
    {
        // se la nave non + stata trovata, il puntatore non punta ad una nave
        // viene dunque lanciata un'eccezione
        throw InvalidMove{};
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