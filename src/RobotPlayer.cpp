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

Position RobotPlayer::get_random_pos()
{
    int x = std::rand() % 12;
    int y = std::rand() % 12;
    return Position(x, y);
}

Position RobotPlayer::get_random_pos(const Position& origin, int size)
{
    if(size > 12/2 + 1) return origin;

    bool done = false;
    int x = std::rand() % 4;
    //x = 0 --> restituisco posizione con stessa ascissa e ordinata maggiore
    //x = 1 --> restituisco posizione con stessa ascissa e ordinata minore
    //x = 2 --> restituisco posizione con stessa ordinata e ascissa maggiore
    //x = 3 --> restituisco posizione con stessa ordinata e ascissa minore
    
    //nel caso la posizione ottenuta randomicamente non vada bene ne cerco un'altra finché non è valida
    while(!done)
    {
        if(x == 0)
        {
            if(origin.Y() + size < 12) return Position(origin.X(), origin.Y() + size);
            //se l'ordinata sfora dal limite allora sottraggo size
            else x = 1;
        }
        else if(x == 1)
        {
            if(origin.Y() - size >= 0) return Position(origin.X(), origin.Y() - size);
            //se l'ordinata sfora dal limite allora aggiungo size
            else x = 0;
        }
        else if(x == 2)
        {
            if(origin.X() + size < 12) return Position(origin.X() + size, origin.Y());
            //se l'ascissa sfora dal limite allora sottraggo size 
            else x = 3;
        }
        else if(x == 3)
        {
            if(origin.X() - size >= 0) return Position(origin.X() - size, origin.Y());
            //se l'ascissa sfora dal limite allora aggiungo size
            else x = 2;
        }
        else done = true;
    }

    //se si arriva a questo pezzo di codice c'è stato un errore quindi restituisco la cella di partenza
    return origin;
    
}

bool RobotPlayer::add_ships(const std::string &cmd, int size)
{
    Position bow = get_random_pos();
    Position stern = get_random_pos(bow, size);
    bool created = DefenseMap().add_ship(bow, stern);

    Direction d = get_direction(bow, stern);
    Position p = (bow + stern) / 2;

    if (created)
    {
        if (size == 5)
        {
            Ironclad ship{d, p, defense_map_, attack_grid_};
            ship_list.push_back(&ship);
        }
        else if (size == 3)
        {
            SupportShip ship{d, p, defense_map_, attack_grid_};
            ship_list.push_back(&ship);
        }
        else
        {
            Submarine ship{p, defense_map_, attack_grid_};
            ship_list.push_back(&ship);
        }
    }
    return true;
}


RobotPlayer::~RobotPlayer() 
{
    Ship* pointer; 
    // dealloco tutta la memoria adelle navi
    for (int i = 0; i < ship_list.size(); i++)
    {
        pointer = ship_list[i]; 
        delete pointer; 
    }
    
    pointer = nullptr; 
}