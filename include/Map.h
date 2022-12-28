#ifndef BATTLESHIPPROJECT_MAP_H_
#define BATTLESHIPPROJECT_MAP_H_

#include "Position.h"
#include "DefenseUnit.h"
#include "AttackUnit.h"
#include "Ship.h"
#include "Submarine.h"
#include "Ironclad.h"
#include "SupportShip.h"
#include <unordered_map>
#include <exception>
#include <vector>
#include <ostream>

class Map
{
    public: 

    // Eccezione che viene lanciata se la posizione non rientra nelle matrici
    class InvalidMapPosition : public std::exception {}; 

    // contruttore di default della classe 
    // che inizializza tutte le matrici come vuote
    Map(); 

    // Funzioni per la DIFESA:

    // ritorna se una determinata posizione è libera nella mappa di difesa
    bool is_free_defense_position(const Position& target_destination) const; 

    // muove una nave dalla sua posizione attuale al target specificato 
    // aggiorna automaticamente la posizione della nave nella collezione se va a buon fine
    // la posizione target origin deve rappresentare il centro della nave da spostare
    // il secondo paramentro è il target destination
    // Ritorna true se lo spostamento è andato a buon fine
    bool move_ship(const Position& target_origin, const Position& target_destination); 

    // sparo ad una nave della mia collezione poichè è stata colpita
    // la funzione verifica se la corazza è arrivata a zero ed in tal caso 
    // la rimuove dalla mappa di difesa e aggiorna la collezione
    // Per tester se una nave è stta affondatat usare la funzione get_ship
    AttackUnit receive_shot(const Position& target_destination); 

    // funzione che cura tutte le navi in un'area 3x3 a partire del centro specificato come target
    // aggiorna automaticamente la corazza delle navi che si trovano nei dintorni della superficie 
    // tenendo allineata con le modifiche la collezione 
    bool fix_ship(const Position& target_origin); 

    // funzione che ritorna le posizioni occupate in un'area 5X5
    // a partire dal centro specificato come target origin. Ritorna le AttackUnit della matrice 5x5 
    // in un vettore che la rappresenta scritta per righe
    std::vector<AttackUnit>& discover_position(const Position& target_destination); 

    // Funzioni per l'ATTACCO: 

    // funzione che permette di impostare come spotted l'area della matrice rappresentata per righe
    // aggiornando la mappa d'attacco
    bool spot_positions(std::vector<AttackUnit>& positions, const Position& center_block); 

    // imposta a hit la cella della mappa d'attacco di target specificato
    bool shot_position(const Position& target_destination, AttackUnit shot_status); 

    // altre funzioni UTILITARIE

    // ritorno la nave presente nel target specificato se presente
    // altrimenti nullptr  
    Ship* get_ship(const Position& center_position); 

    // funzione che permette di aggiungere una nave. 
    // inserisce nel dizionario un acoppia posizione - nave dove il primo parametro è la posizione della prua e il secondo
    // la poppa della nave. Il secondo parametro è un puntatore ad una generica nave. 
    // rotona true se l'operazione è andata buon fine, false se era già presente poichè non ne vogliamo aggiornare il valore. 
    bool add_ship(const Position& bow_position, const Position& stern_position); 


    // Overload dell'operatore << che scrive nell'output stream le matrici d'attacco e di difesa
    std::ostream& operator<<(std::ostream& data_stream); 

    private: 

    // Regione delle costanti da utilizzare nella classe  
    static constexpr int kHeight = 12; 
    static constexpr int kWidth = 12; 
    static constexpr char kEmptySpace = ' '; 
    static constexpr char kHitAndFullSymbol = 'X'; 
    static constexpr char kHitAndEmptySymbol = 'O';
    static constexpr char kIroncladUnitHit = 'c'; 
    static constexpr char kIroncladUnit = 'C';
    static constexpr char kSubmarineUnitHit = 'e'; 
    static constexpr char kSubmarineUnit = 'E';  
    static constexpr char kSupportShipUnitHit = 'c'; 
    static constexpr char kSupportShipUnit = 'C'; 
    static constexpr int kInitiatlShipNumber = 8; 

    // rappresenta la mappa da usare per la difesa
    DefenseUnit defense_map_[kHeight][kWidth]; 
    // rappresenta la mappa da usare per l'attacco
    AttackUnit attack_map_[kHeight][kWidth]; 
    // collezione associativa di navi con Key = posizione del centro e value = puntatore a generica nave
    std::unordered_map<Position, Ship*> ship_dictionary; 
    // verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
    bool check_position(const Position& position) const; 
    // scrivo una nave nella matrice 
    // true se l'operazione è correttamente eseguibile
    bool place_ship(Position& init, Position& end, const Position& center_block, Direction direction); 
    // verifico se la coordinata di centro specificata può essere una posizione plausibile per una nave di lunghezza 
    // length specificata e orientamento orientation.
    // ritorna true se la nave ricoprirebbe una regione non vuota o non rientra nella matrice
    bool check_area_for_placing(const Position& target_destination, int length, Direction orientation) const; 
    // funzione che pulisce tutte le caselle nella regione specificata: centro, lunghezza e direzione
    // le coordinate che andrà a pulire devono essere già testate come corrette!
    void clear_area(const Position& center_block, int length, Direction orientation); 
    
    // l'unica memoria allocata dinamicamente dal programma sta nel dizionario che ha per valori delle coppie
    // le navi. Essendo un elemento della standard library, quando viene invocato il distruttore di default 
    // della classe map che eliminerà l'oggetto ship_dictionary si occuperà lui della deallocazione di ciascuna nave
    // nell'heap
}; 

#endif