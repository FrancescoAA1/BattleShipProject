#include "../include/HumanPlayer.h"
#include <iostream>
Move HumanPlayer::get_move(const std::string &cmd)
{
    // creazione di due posizioni con il costruttore di default
    Position origin{};
    Position target{};
    Move m;

    // prima di dividere la stringa nelle due coordinate
    // si controlla che la stringa corrisponda ad un comando di stampa delle due mappe
    // oppure ad un comando di pulizia della mappa
    if (cmd == "AA AA")
    {
        m.set_movetype(MoveType::showMap);
        return m;
    }
    else if (cmd == "YY YY")
    {
        m.set_movetype(MoveType::clearMap);
        return m;
    }
    else
    {
        // divisione della stringa in due parti (il delimitatore è lo spazio)
        int pos;
        try
        {
            pos = cmd.find_first_of(' ');
        }
        catch (const std::out_of_range& e)
        {
            return m;
        }

        std::cout << std::to_string(pos) << std::endl;
         std::string first_pair = cmd.substr(0, pos);
         std::string second_pair = cmd.substr(pos + 1);

        try
        {
            // per ogni coppia di coordinate viene restituita una posizione
            origin = convert_to_position(first_pair);
            target = convert_to_position(second_pair);

            // viene indivuata la nave che compie l'azione
            Ship *ship_cmd = get_ship(origin);

            if (ship_cmd)
            {
                // distinzione del tipo di mossa a seconda della taglia della nave restituita
                // NOTA: sarebbe opportuno usare delle costanti
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
        catch (InvalidPosition)
        {
            return {origin, target, MoveType::invalid};
        }
    }
}

bool HumanPlayer::add_ships(const std::string &cmd, int size)
{
    Position bow{};
    Position stern{};

    // divisione della stringa in due parti (il delimitatore è lo spazio)
    int pos = cmd.find_first_of(' ');
    std::string first_pair = cmd.substr(0, pos);
    std::string second_pair = cmd.substr(pos + 1);

    // per ogni coppia di coordinate viene restituita una posizione
    bow = convert_to_position(first_pair);
    stern = convert_to_position(second_pair);

    int c_size = get_size(bow, stern);

    if (c_size == size)
    {
        if (defense_map_.add_ship(bow, stern))
        {

            Direction d = get_direction(bow, stern);
            Position p = (bow + stern) / 2;
            if (size == 5)
            {
                Ironclad *ship = new Ironclad{d, p, defense_map_, attack_grid_};
                ship_list.push_back(ship);
            }
            else if (size == 3)
            {
                SupportShip *ship = new SupportShip{d, p, defense_map_, attack_grid_};
                ship_list.push_back(ship);
            }
            else
            {
                Submarine *ship = new Submarine{p, defense_map_, attack_grid_};
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

    return true;
}