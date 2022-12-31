#include "../include/Player.h"

Player::Player(const std::string &nickname)
{
    nickname_ = nickname;
    attack_grid_ = AttackGrid();
    defense_map_ = DefenseMap();
    // il vector di navi è inizialmente vuoto
    ship_list;
    current_move;
}

// metodi privati
std::vector<AttackUnit> &Player::retrieve_unit(const Position &target)
{
    std::vector<AttackUnit> att = defense_map_.spot_area(target, 5);
    return att;
}

// metodi privati
AttackUnit Player::receive_attack(const Position &target)
{
    std::pair shot_info = defense_map_.receive_shot(target);
    Position p = shot_info.first;

    if (!p.is_absolute_invalid())
    {
        Ship *ship_attacked = get_ship(shot_info.first);
        bool sunk = ship_attacked->hit();
        if (sunk)
        {
            // da implementare rimozione navi dalla lista

            // std::vector<int>::iterator pos = std::find(ship_list.begin(), ship_list.end(), ship_attacked);
            // if (pos != ship_list.end())
            //     ship_list.erase(pos);

            defense_map_.remove_ship(p);
        }
    }

    return shot_info.second;
}

std::vector<AttackUnit> Player::execute_move(const Position &target, const MoveType &type)
{
    std::vector<AttackUnit> units;

    if (type == MoveType::attack)
    {
        units = {receive_attack(target)};
    }
    else if (type == MoveType::moveAndDiscover)
    {
        units = {retrieve_unit(target)};
    }

    return units;
}

void Player::handle_response(std::vector<AttackUnit> units)
{
    Ship *ship = get_ship(current_move.origin());
    ship->action(current_move.target(), units);
}

bool Player::check_for_graphic_cmd()
{
    if (current_move.movetype() == MoveType::clearMap)
    {
        // da implementare
        AttackGrid().clear_area();
        current_move.makeInvalid();
    }
    else if (current_move.movetype() == MoveType::showMap)
    {
        // da implementare
        // std::cout << player_2->defenseMap();
        // std::cout << player_2->attackMap();
        current_move.makeInvalid();
    }
}

Position &Player::convert_to_position(const std::string &coordinate)
{
    try
    {
        // sottrazione del valore ASCII di 'A' al primo carattere della stringa
        // conversione da char ad int
        int x = coordinate[0] - kDefaultCapitalAscii;

        // conversione da stringa ad intero dell'ultima parte della coppia di coordinate (numero)
        // stoi lancia std::invalid_argument exception se la sottostringa non è un numero
        // ATTENZIONE (da verificare in fase di debug) potrebbe essere necessario controllare che numero di cifre
        // di y corrisponda alla lunghezza della sottostringa;
        int y = std::stoi(coordinate.substr(1, coordinate.size() - 1));

        // controllo che x e y siano nel range delle dimensioni delle due mappe
        // NOTA: sarebbe opportuno poter accedere alle costanti di dimensione della mappa
        if ((x >= 0 || x <= 11) && (y >= 0 || y <= 11))
        {
            Position pos{x, y};
            return pos;
        }

        // se una delle due cooridnate non è valida, viene lanciata un'eccezione
        throw InvalidPosition{};
    }
    catch (std::invalid_argument)
    {
        throw InvalidPosition{};
    }
}

std::string &Player::convert_to_command(const Position &position)
{
    // conversione esplicita da int ad a char (sicura) della coordinata X della posizione
    // stringa formata dal carattere a cui viene sommato il valore ASCII di "A"
    std::string letter(1, (char)position.X() + kDefaultCapitalAscii);

    // conversione da int a string della coordinata Y della posizione
    std::string number = std::to_string(position.Y());

    // concatenazione delle due stringhe contenenti le coordinate in formato (A1)
    std::string coordinate = letter + number;
    return coordinate;
}

Ship *Player::get_ship(const Position &origin)
{
    // ricerca del puntatore alla nave avente come centro la posizione di origine
    auto it = std::find_if(ship_list.begin(), ship_list.end(), [origin](Ship *ship)
                           { return ship->centre() == origin; });

    // se l'iteratore ritornato dall'algoritmo STL punta all'ultimo elemento del vettore di navi
    // la nave non è stata trovata e viene ritornato nullptr, altrimenti si calcola l'indice
    // del vettore in cui trova il puntatore e lo si restituisce.

    if (it != ship_list.end())
    {
        return *it;
    }
    else
    {
        return nullptr;
    }
}

bool Player::add_ship(const std::string &cmd)
{
    Position bow{};
    Position stern{};

    // divisione della stringa in due parti (il delimitatore è lo spazio)
    int pos = cmd.find_first_of(' ');
    std::string first_pair = cmd.substr(pos + 1);
    std::string second_pair = cmd.substr(0, pos);

    // per ogni coppia di coordinate viene restituita una posizione
    bow = convert_to_position(first_pair);
    stern = convert_to_position(second_pair);

    if (defense_map_.add_ship(bow, stern))
    {
        int size = get_size(bow, stern);
        Direction d = get_direction(bow, stern);
        Position p = (bow + stern) / 2;

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
    else
    {
        return false;
    }

    return true;
}

// fornisce la direzione della nave da inserire
Direction get_direction(const Position &bow, const Position &stern)
{
    Direction ship_dir;
    if (bow.X() == stern.X())
    {
        return Direction::vertical;
    }
    return Direction::horizontal;
}

// fornisce la taglia della nave da inserire
int get_size(const Position &bow, const Position &stern)
{
    Direction placing = get_direction(bow, stern);

    if (placing == Direction::horizontal)
    {
        return abs(bow.X() - stern.X());
    }
    else
        return abs(bow.Y() - stern.Y());
}
