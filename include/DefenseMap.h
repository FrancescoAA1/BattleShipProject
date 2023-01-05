#ifndef BATTLESHIPPROJECT_DEFENSEMAP_H_
#define BATTLESHIPPROJECT_DEFENSEMAP_H_

#include "Position.h"
#include "DefenseUnit.h"
#include "AttackUnit.h"
#include "Direction.h"
#include <ostream>
#include <utility>
#include <vector>

class DefenseMap
{
    public:
    // le costanti delle dimesnioni possono essere pubbliche e accessibili dall'estreno 
    static constexpr int kHeight = 12; 
    static constexpr int kWidth = 12; 

    // contruttore di default della classe 
    // che inizializza tutte le matrici come vuote
    DefenseMap(); 

    // Funzioni per la DIFESA:

    // ritorna se una determinata posizione è libera nella mappa di difesa
    bool is_free_defense_position(const Position& target_destination) const; 

    // muove una nave dalla sua posizione attuale al target specificato 
    // la posizione target origin deve rappresentare il centro della nave da spostare
    // il secondo paramentro è il target destination
    // Ritorna true se lo spostamento è andato a buon fine
    bool move_ship(const Position& target_origin, const Position& target_destination); 

    // sparo ad una nave della mia collezione poichè è stata colpita
    // ritorno una poccia (posizione del centro della nave colpita, stato dell'attacco)
    // se il tiro non è andato a segno allora ritorna O e la posizione del centro invalida
    // Se la nave è stata affondata richiamare il metodo remove ship se si desidera rimuovere dalla mappa 
    std::pair<Position, AttackUnit> receive_shot(const Position& target_destination); 

    // funzione che permette di rimuovere una nave dalla mappa 
    bool remove_ship(const Position& target_origin);

    // funzione che permette di ottenere i centri delle navi nell'area specificata di lato side centrata nel punto
    // target_origin specificato
    // se l'area fuoriesce dalla matrice ne fa l'intersezione. Se l'area è più vasta della matrice e 
    // la contiene => ritorna tutti i centri della matrice
    std::vector<Position> discovers_neighbors(const Position& target_origin, int side) const; 

    // funzione che cura la nave con centro specificato in target_origin
    bool fix_ship(const Position& target_origin); 

    // funzione che scopre tutte le navi in un'area dimxdim a partire del centro specificato come target
    // ritona un'area che rappresenta una matrice dimxdim scritta per righe
    // l'intero serve a specificare il lato di dimensione per l'area
    // se l'area non riesntra nella matrice ne fa l'intersezione 
    // se l'area contiene la matrice ritorna tutta la matrice 
    std::vector<AttackUnit> spot_area(const Position& target_origin, int side) const;  

    // altre funzioni UTILITARIE

    // funzione che permette di aggiungere una nave. 
    // il primo parametro è la posizione della prua e il secondo è la poppa della nave
    // ritorna true se l'operazione è andata buon fine, false se era già presente poichè non ne vogliamo aggiornare il valore. 
    bool add_ship(const Position& bow_position, const Position& stern_position); 

    // funzione che scrive in una stringa la mappa 
    std::string to_string() const; 

    // verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
    bool check_position(const Position& position) const; 

    private: 

    // Regione delle costanti da utilizzare nella classe  
    static constexpr char kEmptySpace = ' '; 
    static constexpr char kIroncladUnitHit = 'c'; 
    static constexpr char kIroncladUnit = 'C';
    static constexpr char kSubmarineUnitHit = 'e'; 
    static constexpr char kSubmarineUnit = 'E';  
    static constexpr char kSupportShipUnitHit = 's'; 
    static constexpr char kSupportShipUnit = 'S'; 
    static constexpr char kFirstRowLetter = 'A'; 
    static constexpr int kFirstColumnNumber = 1;
    static constexpr int kShipType1Dim = 1;
    static constexpr int kShipType2Dim = 3;  
    static constexpr int kShipType3Dim = 5; 

    // rappresenta la mappa da usare per la difesa
    DefenseUnit defense_map_[kHeight][kWidth]; 
    // scrivo una nave nella matrice
    // inizio e fine devono già condividere la stessa riga o la stessa colonna in accordo con la direzione 
    // true se l'operazione è correttamente eseguibile
    // init e end le passo per valore poichè verranno modificate all'interno
    bool place_ship(Position init, Position end, const Position& new_center_block, const Position& old_center_block, int block_dimension, Direction direction); 
    // verifico se la coordinata di centro specificata può essere una posizione plausibile per una nave di lunghezza 
    // length specificata e orientamento orientation.
    // ritorna true se la nave ricoprirebbe una regione non vuota o non rientra nella matrice
    bool check_area_for_placing(const Position& target_destination, const Position& origin_block_center, int length, Direction orientation) const; 
    // funzione che pulisce tutte le caselle nella regione specificata: centro, lunghezza e direzione
    // le coordinate che andrà a pulire devono essere già testate come corrette!
    void clear_area(const Position& center_block, int length, Direction orientation); 
    // metodo che resetta tutta la matrice di difesa
    void clear_defense_map(); 
    // funzione che verifica se un'area è accerchiata
    bool is_sorrounded(const Position& target_origin, int size, Direction orientation) const; 
    // funzione che ritorna se ci sono blocchi con centro uguale al target
    bool center_block_discovery(const Position& center_block) const; 
}; 

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream& operator<<(std::ostream& data_stream, const DefenseMap& defense_map); 

#endif