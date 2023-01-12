#include "../include/RobotPlayer.h"
#include "../include/Utility.h"
#include <iostream>
#include <chrono>
#include <thread>

// il robot inventa la mossa per cui la stringa passata come parametro sarà vuota
Move RobotPlayer::get_move(const std::string &move)
{
    Position origin{};
    Position target{};
    Move m;

    int size_list = ship_list.size();
    std::shared_ptr<Ship> ship_cmd;

    // se esiste almeno una nave nella lista, ne viene prelevata una in modo casuale
    if (size_list > 0)
    {
        ship_cmd = ship_list.at(get_random(ship_list.size()));
    }
    else
    {
        ship_cmd = nullptr;
    }

    // se la nave è stata prelevata, tale nave eseguirà l'azione
    if (ship_cmd)
    {
        // posizione di origine corrisponde al centro della nave appena ottenuta
        origin = ship_cmd->centre();
        // viene generato una posizione target casuale
        target = get_random_pos();

        int size = ship_cmd->size();

        // distinzione del tipo di mossa a seconda della taglia della nave restituita
        // NOTA: sarebbe opportuno usare delle costanti
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

Position RobotPlayer::get_random_pos()
{
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    // srand(time(NULL));
    int x = abs(get_random(defense_map_.kWidth));
    int y = abs(get_random(defense_map_.kHeight));
    return Position(x, y);
}

Position RobotPlayer::get_random_pos(const Position &origin, int size)
{
    if (size > defense_map_.kHeight / 2 + 1)
        return origin;

    bool done = false;
    // x = 0 --> restituisco posizione con stessa ascissa e ordinata maggiore
    // x = 1 --> restituisco posizione con stessa ascissa e ordinata minore
    // x = 2 --> restituisco posizione con stessa ordinata e ascissa maggiore
    // x = 3 --> restituisco posizione con stessa ordinata e ascissa minore

    // nel caso la posizione ottenuta randomicamente non vada bene ne cerco un'altra finché non è valida
    while (!done)
    {
        int x = abs(get_random(4));
        if (x == 0)
        {
            int y = origin.Y() + size - 1;
            if (y <= 11)
                return Position(origin.X(), y);
            // se l'ordinata sfora dal limite allora sottraggo size
            else
                x = 1;
        }
        else if (x == 1)
        {
            int y = origin.Y() - size + 1;
            if (y >= 0)
                return Position(origin.X(), y);
            // se l'ordinata sfora dal limite allora aggiungo size
            else
                x = 0;
        }
        else if (x == 2)
        {
            int x = origin.X() + size - 1;
            if (x <= 11)
                return Position(x, origin.Y());
            // se l'ascissa sfora dal limite allora sottraggo size
            else
                x = 3;
        }
        else if (x == 3)
        {
            int x = origin.X() - size + 1;
            if (x >= 0)
                return Position(x, origin.Y());
            // se l'ascissa sfora dal limite allora aggiungo size
            else
                x = 2;
        }
        else
            done = true;
    }

    // se si arriva a questo pezzo di codice c'è stato un errore quindi restituisco la cella di partenza
    return origin;
}

bool RobotPlayer::add_ships(const std::string &cmd, int size, FileWriter &fw)
{
    // vengono generate posizioni casuali di prua e poppa
    Position bow = get_random_pos();
    // la generazione della posizione di poppa è basata su quella della prua
    Position stern = get_random_pos(bow, size);

    // si controlla se la nave può essere inserita nella mappa
    bool created = defense_map_.add_ship(bow, stern);

    Direction d = get_direction(bow, stern);
    Position p = (bow + stern) / 2;

    // se l'inserimento è andato a buon fine, a seconda del tipo di nave,
    // viene chiamato il relativo costruttore
    // infine, la nave appena istanziata viene aggiunta alla lista di navi
    if (created)
    {
        if (size == Ironclad::kSize)
        {
            std::shared_ptr<Ironclad> ship(new Ironclad{d, p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
            std::cout << "Corazzata Aggiunta in Con Comando " << convert_to_command(bow) << " " << convert_to_command(stern);
        }
        else if (size == SupportShip::kSize)
        {
            std::shared_ptr<SupportShip> ship(new SupportShip{d, p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
            std::cout << "Nave di Supporto Aggiunta in Con Comando " << convert_to_command(bow) << " " << convert_to_command(stern);
        }
        else
        {
            std::shared_ptr<Submarine> ship(new Submarine{p, defense_map_, attack_grid_});
            ship_list.push_back(ship);
            std::cout << "Sottomarino Aggiunto in Con Comando " << convert_to_command(bow) << " " << convert_to_command(stern);
        }

        std::string cmd_line = convert_to_command(bow) + " " + convert_to_command(stern);
        fw.write_line(cmd_line);

        return true;
    }
    return false;
}