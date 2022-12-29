#ifndef BATTLESHIPPROJECT_PLAYER_H_
#define BATTLESHIPPROJECT_PLAYER_H_

#include <string>
#include <vector>
#include <algorithm>
#include "AttackMap.h"
#include "DefenseMap.h"
#include "Move.h"
#include "Ship.h"

class Player
{
    public:


    // Eccezione che viene lanciata se la posizione di origine non è presente nel vettore di navi
    class ShipNotPlaceable : public std::exception {};

    // Eccezione che viene lanciata se la mossa creata non è valida
    class InvalidMove : public std::exception {}; 

    // Eccezione che viene lanciata se la posizione di origine non è presente nel vettore di navi
    class InvalidPosition : public std::exception {};
    
    //funzione virtuale pura di cui effettuare l'override nelle classi derivate
    //a partire da un comando ricava la mossa che verrà effettuata dalla nave
    //specificando posizione di origine, posizione target e tipo di mossa;
    //lancia eccezioni di tipo invalidMove
    virtual Move get_move(const std::string& cmd) = 0;

    //funzione che converte una coppia di coordinate (quindi una delle due parti dell'intero comando)
    //in una posizione
    Position& convert_to_position(const std::string& coordinate);

    //funzione che converte una posizione in una delle due parti del comando
    std::string& convert_to_command(const Position& position);

    //data una posizione di origine, la funzione restituisce un puntatore alla nave 
    //avente come centro la posizione specificata. Se tale nave non esiste
    //la funzione ritorna nullptr
    Ship* get_ship(const Position& origin); 

    //funzione che aggiunge una nave alla lista dopo aver richiesto alla mappa di controllare
    //le coordinate di prua e poppa
    //Restituisce true se la nave è stata aggiunta, altrimenti false
    bool add_ship(const std::string& cmd);

    //funzione che ritorna un vettore di attackUnit per le operazioni di attacco e sonar
    std::vector<AttackUnit>& retrieve_unit(const Position& target, const MoveType& move);

    //metodi getter
    std::string nickname() {return nickname_;}

    protected:

    //costruttore dato il nome del giocatore
    Player(const std::string&);
        
    //nome del giocatore
    std::string nickname_;

    //mappa di attacco del giocatore
    AttackMap attack_map_;

    //mappa di difesa del giocatore
    DefenseMap defense_map_;

    //vector di puntatori ad una nave
    std::vector<Ship*> ship_list;

    private :
    
    //costante utile per le conversioni da comando a posizione e viceversa
    static constexpr int kDefaultCapitalAscii = 65;

    //costante utile per le conversioni da comando a posizione e viceversa
    static constexpr int kEqualityVectorPosition =1;

}; 

#endif