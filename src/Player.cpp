#include "../include/Player.h"
#include <iostream>

Player::Player(const std::string &nickname)
{
    nickname_ = nickname;
    attack_grid_ = AttackGrid();
    defense_map_ = DefenseMap();
    // il vector di navi è inizialmente vuoto perchè vengono aggiunte con push_back
    ship_list = std::vector<Ship *>(0);
}

// metodi privati
std::vector<AttackUnit> Player::retrieve_unit(const Position &target)
{
    std::vector<AttackUnit> att = defense_map_.spot_area(target, 5);
    return att;
}

// metodi privati
AttackUnit Player::receive_attack(const Position &target)
{
    //la mappa del giocatore che riceva la mossa viene aggiornata
    std::pair<Position, AttackUnit> shot_info = defense_map_.receive_shot(target);
    //posizione da analizzare
    Position p = shot_info.first;

    if (!p.is_absolute_invalid())
    {
        //controllo se è presente una nave nella posizione restituita da receive shot
        Ship *ship_attacked = get_ship(p);

        if (ship_attacked)
        {
            bool sunk = ship_attacked->hit();
            //se la nave è stata affondata, viene rimossa dalla lista delle navi
            if (sunk)
            {
                std::cout << "Nave Affondata!";
                ship_list.erase(std::remove(ship_list.begin(), ship_list.end(), ship_attacked), ship_list.end());

                defense_map_.remove_ship(p);
            }
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

void Player::handle_response(std::vector<AttackUnit> units, const Move &m)
{
    //LA NAVE INCARICATA DI COMPIERE L'AZIONE VIENE TROVATA
    Ship *ship = get_ship(m.origin());
    //IL GIOCATORE FA ESEGUIRE L'AZIONE ALLA NAVE INCARICATA
    ship->action(m.target(), units);
}

bool Player::check_for_graphic_cmd(Move &m)
{
    /*
    if (m.movetype() == MoveType::clearMap)
    {
        // da implementare
        AttackGrid().clear_area();
        m.makeInvalid();
    }
    else if (m.movetype() == MoveType::showMap)
    {
        // da implementare
        // std::cout << player_2->defenseMap();
        // std::cout << player_2->attackMap();
        m.makeInvalid();
    }
*/
    // se si arriva qui qualcosa è andato storto
    return m.movetype() == MoveType::clearMap || m.movetype() == MoveType::showMap;
}

Position Player::convert_to_position(const std::string &coordinate)
{
    Position pos{};

    try
    {
        // sottrazione del valore ASCII di 'A' al primo carattere della stringa
        // conversione da char ad int
        int x = coordinate[0] - kDefaultCapitalAscii;

        // conversione da stringa ad intero dell'ultima parte della coppia di coordinate (numero)
        // stoi lancia std::invalid_argument exception se la sottostringa non è un numero
        // ATTENZIONE (da verificare in fase di debug) potrebbe essere necessario controllare che numero di cifre
        // di y corrisponda alla lunghezza della sottostringa;
        int y = std::stoi(coordinate.substr(1, coordinate.size() - 1)) - 1;

        // controllo che x e y siano nel range delle dimensioni delle due mappe
        // NOTA: sarebbe opportuno poter accedere alle costanti di dimensione della mappa
        if (x >= 0 && x <= 11 && y >= 0 && y <= 11)
        {
            pos = Position(x, y);
            return pos;
        }
        else
        {
            // se una delle due cooridnate non è valida, viene ritornata posizione non valida
            pos.make_absolute_invalid();
            return pos;
        }
    }
    catch (std::invalid_argument)
    {
        pos.make_absolute_invalid();
        return pos;
    }
}

std::string Player::convert_to_command(const Position &position)
{
    if (position.X() >= 0 && position.X() <= 11 && position.Y() >= 0 && position.Y() <= 11)
    {

        // conversione esplicita da int ad a char (sicura) della coordinata X della posizione
        // stringa formata dal carattere a cui viene sommato il valore ASCII di "A"
        std::string letter(1, (char)position.X() + kDefaultCapitalAscii);

        // conversione da int a string della coordinata Y della posizione
        std::string number = std::to_string(position.Y() + 1);

        // concatenazione delle due stringhe contenenti le coordinate in formato (A1)
        std::string coordinate = letter + number;
        return coordinate;
    }

    throw InvalidPosition{};
}

Ship *Player::get_ship(const Position origin)
{
    // ricerca del puntatore alla nave avente come centro la posizione di origine
    auto it = std::find_if(ship_list.begin(), ship_list.end(), [origin](Ship *ship) -> bool
                           { return (ship->centre() == origin); });

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
        return abs(bow.X() - stern.X()) + 1;
    }
    else
        return abs(bow.Y() - stern.Y()) + 1;
}

Player::~Player()
{
    Ship *pointer;
    // dealloco tutta la memoria adelle navi
    for (int i = 0; i < ship_list.size(); i++)
    {
        pointer = ship_list[i];
        delete pointer;
    }

    pointer = nullptr;
}
