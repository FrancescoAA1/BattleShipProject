#include "../include/Player.h"

Player::Player(const std::string &nickname)
{
    nickname_ = nickname;
    attack_map_ = AttackMap();
    defense_map_ = DefenseMap();
    // il vector di navi è inizialmente vuoto
    ship_list;
}

std::vector<AttackUnit> &Player::retrieve_unit(const Position &target, const MoveType &move)
{
    //metodo da ripensare in seguito alla creazione della classe Game e del controller
    std::vector<AttackUnit> att;
    if (move == MoveType::attack)
    {
        att = {defense_map_.receive_shot(target)};
        return att;
    }
    else if (move == MoveType::moveAndDiscover)
    {
        att = defense_map_.spot_area(target, 5);
        return att;
    }
    else
    {
        return att;
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
        //stoi lancia std::invalid_argument exception se la sottostringa non è un numero
        //ATTENZIONE (da verificare in fase di debug) potrebbe essere necessario controllare che numero di cifre
        //di y corrisponda alla lunghezza della sottostringa;
        int y = std::stoi(coordinate.substr(1, coordinate.size() - 1));

        //controllo che x e y siano nel range delle dimensioni delle due mappe
        //NOTA: sarebbe opportuno poter accedere alle costanti di dimensione della mappa
        if ((x >= 0 || x <= 11) && (y >= 0 || y <= 11))
        {
            Position pos{x, y};
            return pos;
        }

        //se una delle due cooridnate non è valida, viene lanciata un'eccezione
        throw InvalidPosition{};
    }
    catch(std::invalid_argument)
    {
        throw InvalidPosition{};
    }
}

std::string &Player::convert_to_command(const Position &position)
{
    //conversione esplicita da int ad a char (sicura) della coordinata X della posizione
    //stringa formata dal carattere a cui viene sommato il valore ASCII di "A"
    std::string letter(1, (char)position.X() + kDefaultCapitalAscii);

    //conversione da int a string della coordinata Y della posizione
    std::string number = std::to_string(position.Y());

    //concatenazione delle due stringhe contenenti le coordinate in formato (A1)
    std::string coordinate = letter + number;
    return coordinate;
}

Ship *Player::get_ship(const Position &origin)
{
    //ricerca del puntatore alla nave avente come centro la posizione di origine
    auto it = std::find_if(ship_list.begin(), ship_list.end(), [origin](const Ship &ship)
                           { return ship.centre() == origin; });

    //se l'iteratore ritornato dall'algoritmo STL punta all'ultimo elemento del vettore di navi
    //la nave non è stata trovata e viene ritornato nullptr, altrimenti si calcola l'indice
    //del vettore in cui trova il puntatore e lo si restituisce.
    if (it != ship_list.end())
    {
        auto index = std::distance(ship_list.begin(), it);
        return ship_list.at(index);
    }
    else
    {
        return nullptr;
    }
}