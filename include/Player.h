#ifndef BATTLESHIPPROJECT_PLAYER_H_
#define BATTLESHIPPROJECT_PLAYER_H_

#include <string>
#include <vector>
#include <algorithm>
#include "DefenseMap.h"
#include "AttackGrid.h"
#include "Move.h"
#include "Ship.h"
#include "Ironclad.h"
#include "SupportShip.h"
#include "Submarine.h"

class Player
{
public:
    // Eccezione che viene lanciata se la posizione di origine non è presente nel vettore di navi
    class InvalidPosition : public std::exception
    {
    };

    // funzione virtuale pura di cui effettuare l'override nelle classi derivate
    // a partire da un comando ricava la mossa che verrà effettuata dalla nave
    // specificando posizione di origine, posizione target e tipo di mossa;
    // lancia eccezioni di tipo invalidMove
    virtual Move get_move(const std::string &cmd) = 0;

      // funzione che aggiunge una nave alla lista dopo aver richiesto alla mappa di controllare
    // le coordinate di prua e poppa
    // Restituisce true se la nave è stata aggiunta, altrimenti false
    virtual bool add_ships(const std::string &cmd, int size) = 0;

    // funzione che converte una coppia di coordinate (quindi una delle due parti dell'intero comando)
    // in una posizione
    Position convert_to_position(const std::string &coordinate);

    // funzione che converte una posizione in una delle due parti del comando
    std::string convert_to_command(const Position &position);

    // data una posizione di origine, la funzione restituisce un puntatore alla nave
    // avente come centro la posizione specificata. Se tale nave non esiste
    // la funzione ritorna nullptr
    Ship *get_ship(const Position origin);

    // funzione che ritorna un vettore di attackUnit per l' operazione del sottomarino
    std::vector<AttackUnit> retrieve_unit(const Position &target);

    // funzione che identifica richiede l'aggiornamento della mappa di difesa e, nel caso di nave afffondata
    // della lista delle navi
    AttackUnit receive_attack(const Position &target);

    // funzione che richiede l'aggiornamento della mappa per il giocatore che riceve una data mossa
    std::vector<AttackUnit> execute_move(const Position &target, const MoveType &type);

    // funzione che gestisce la ricezione di attackunits dal giocatore avversario
    void handle_response(std::vector<AttackUnit> units, const Move &m);

    // funzione che verifica se il comando scelto dal giocatore
    // è un comando per visualizzare la mappa o pulirla
    // ed esegue eventualmente tale azione
    bool check_for_graphic_cmd(Move &m);

    // metodi getter
    std::string nickname() { return nickname_; }
    AttackGrid &attack_grid() { return attack_grid_; }
    DefenseMap &defense_map() { return defense_map_; }
    int get_ships_left() { return ship_list.size(); }

    virtual ~Player(); 


protected:
    // costruttore dato il nome del giocatore
    Player(const std::string &);

    // nome del giocatore
    std::string nickname_;

    // mappa di attacco del giocatore
    AttackGrid attack_grid_;

    // mappa di difesa del giocatore
    DefenseMap defense_map_;

    // vector di puntatori ad una nave
    std::vector<Ship *> ship_list;

private:
    // costante utile per le conversioni da comando a posizione e viceversa
    static constexpr int kDefaultCapitalAscii = 65;

    // costante utile per le conversioni da comando a posizione e viceversa
    static constexpr int kEqualityVectorPosition = 1;
};

// fornisce la direzione della nave da inserire
Direction get_direction(const Position &bow, const Position &stern);

// fornisce la taglia della nave da inserire
int get_size(const Position &bow, const Position &stern);

#endif