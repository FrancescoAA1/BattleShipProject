#include "../include/Player.h"
#include "../include/Utility.h"
#include <iostream>

Player::Player(const std::string &nickname)
{
    nickname_ = nickname;
    attack_grid_ = AttackGrid();
    defense_map_ = DefenseMap();
    // il vector di navi è inizialmente vuoto perchè vengono aggiunte con push_back
    ship_list = std::vector<std::shared_ptr<Ship>>(0);
}

std::vector<AttackUnit> Player::retrieve_unit(const Position &target)
{
    // il giocatore avversario restituisce un vettore di attackUnit che indicano
    // le navi presenti nella zona 5x5 a partire dal centro passato come parametro
    std::vector<AttackUnit> att = defense_map_.spot_area(target, 5);
    return att;
}

AttackUnit Player::receive_attack(const Position &target)
{
    // la mappa del giocatore che riceva l'attacco della corazzata nemica viene aggiornata
    std::pair<Position, AttackUnit> shot_info = defense_map_.receive_shot(target);
    // posizione da analizzare
    Position p = shot_info.first;

    // controllo che la posizione sia valida
    if (!p.is_absolute_invalid())
    {
        // controllo se è presente una nave nella posizione restituita da receive shot
        std::shared_ptr<Ship> ship_attacked = get_ship(p);

        if (ship_attacked)
        {
            bool sunk = ship_attacked->hit();

            // se la nave è stata affondata, viene rimossa dalla lista delle navi e conseguentemente
            // dalla mappa
            if (sunk)
            {
                ship_list.erase(std::remove(ship_list.begin(), ship_list.end(), ship_attacked), ship_list.end());
                defense_map_.remove_ship(p);
            }
        }
    }
    // il giocatore avversario restituisce lo stato della cella appena colpita
    return shot_info.second;
}

std::vector<AttackUnit> Player::execute_move(const Position &target, const MoveType &type)
{
    std::vector<AttackUnit> units;

    // se la mossa è effettuata da una corazzata
    if (type == MoveType::attack)
    {
        units = {receive_attack(target)};
    }
    // se la mossa è effettuata da un sonar
    else if (type == MoveType::moveAndDiscover)
    {
        units = {retrieve_unit(target)};
    }

    // nel caso di mossa effettuata da nave di supporto, il vettore di attackUnit
    // è giustamente vuota, perchè la mossa non interessa il giocatore avversario
    return units;
}

bool Player::handle_response(std::vector<AttackUnit> units, const Move &m)
{
    // la nave incaricata di compiere l'azione viene trovata
    std::shared_ptr<Ship> ship = get_ship(m.origin());
    // il giocatore fa eseguire l'azione alla nace incaricata
    bool action_done = ship->action(m.target(), units);

    // DA FARE COMPIERE ALLA NAVE
    if (action_done && (m.movetype() == MoveType::moveAndFix || m.movetype() == MoveType::moveAndDiscover))
    {
        // dopo che lo spostamento è avvenuto con successo
        // il centro della nave viene spostato
        ship->set_center(m.target());
    }

    return action_done;
}

std::shared_ptr<Ship> Player::get_ship(const Position origin)
{
    // ricerca del puntatore alla nave avente come centro la posizione di origine
    auto it = std::find_if(ship_list.begin(), ship_list.end(), [origin](std::shared_ptr<Ship> ship) -> bool
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

bool Player::check_graphic_cmd(const Move &m)
{
    if (m.movetype() != MoveType::invalid)
    {
        if (m.movetype() == MoveType::clearSonared) // AA AA
        {
            this->attack_grid().clear_sonared();
            std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        }
        else if (m.movetype() == MoveType::clearFullHit) // BB BB
        {
            this->attack_grid().clear_all_full_and_hit();
            std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        }
        else if (m.movetype() == MoveType::clearEmptyHit) // CC CC
        {
            this->attack_grid().clear_all_full_and_empty();
            std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        }
        else if (m.movetype() == MoveType::showMap)
        {
            std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }

    // qualunque sia il comando grafico scelto, è necessario stampare la mappa
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
        return abs(bow.X() - stern.X()) + 1;
    }
    else
        return abs(bow.Y() - stern.Y()) + 1;
}

Player::~Player()
{
    std::shared_ptr<Ship> pointer;
    // dealloco tutta la memoria adelle navi
    for (int i = 0; i < ship_list.size(); i++)
    {
        pointer = ship_list[i];
        // delete pointer;
    }

    pointer = nullptr;
}
