#include "../include/HumanPlayer.h"

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
        origin.make_absolute_invalid();
        target.make_absolute_invalid();
        return Move{origin, target, MoveType::showMap};
    }
    else if (cmd == "YY YY")
    {
        origin.make_absolute_invalid();
        target.make_absolute_invalid();
        return Move{origin, target, MoveType::clearMap};
    }
    else
    {
        // divisione della stringa in due parti (il delimitatore è lo spazio)
        int pos = cmd.find_first_of(' ');
        std::string first_pair = cmd.substr(pos + 1);
        std::string second_pair = cmd.substr(0, pos);

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
        catch (InvalidPosition)
        {
            m = {origin, target, MoveType::invalid};
            current_move = m;
            return m;
        }
    }
}