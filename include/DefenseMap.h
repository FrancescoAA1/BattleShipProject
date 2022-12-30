#ifndef BATTLESHIPPROJECT_DEFENSEMAP_H_
#define BATTLESHIPPROJECT_DEFENSEMAP_H_

#include "Position.h"
#include "DefenseUnit.h"
#include "AttackUnit.h"
#include "Direction.h"
#include <ostream>
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
    // ritorno un blocco di attacco per rappresentare lo stato finale dell'operazione da comunicare 
    // all'esterno.
    // Se la nave è stata affondata richiamare il metodo remove ship se si desidera rimuovere dalla mappa 
    AttackUnit receive_shot(const Position& target_destination); // ritonare un pair 

    // Metodo che permette di rimuovere una nave dalla mappa 
    bool remove_ship(const Position& target_origin); 

    // funzione che cura tutte le navi in un'area dimxdim a partire del centro specificato come target
    // l'intero serve a specificare il lato di diemnsione per l'area
    std::vector<Position>& fix_ship(const Position& target_origin, int dim); 

    // funzione che scopre tutte le navi in un'area dimxdim a partire del centro specificato come target
    // ritona un'area che rappresenta una matrice dimxdim scritta per righe
    // l'intero serve a specificare il lato di diemnsione per l'area
    std::vector<AttackUnit>& spot_area(const Position& target_origin, int dim);  

    // altre funzioni UTILITARIE

    // funzione che permette di aggiungere una nave. 
    // il primo parametro è la posizione della prua e il secondo è la poppa della nave
    // rotorna true se l'operazione è andata buon fine, false se era già presente poichè non ne vogliamo aggiornare il valore. 
    bool add_ship(const Position& bow_position, const Position& stern_position); 


    // Overload dell'operatore << che scrive nell'output stream la matrice di difesa
    std::ostream& operator<<(std::ostream& data_stream); 

    private: 

    // Regione delle costanti da utilizzare nella classe  
    static constexpr int kHeight = 12; 
    static constexpr int kWidth = 12; 
    static constexpr char kEmptySpace = ' '; 
    static constexpr char kIroncladUnitHit = 'c'; 
    static constexpr char kIroncladUnit = 'C';
    static constexpr char kSubmarineUnitHit = 'e'; 
    static constexpr char kSubmarineUnit = 'E';  
    static constexpr char kSupportShipUnitHit = 'c'; 
    static constexpr char kSupportShipUnit = 'C'; 
    static constexpr char kFirstRowLetter = 'A'; 
    static constexpr int kFirstColumnNumber = 1; 

    // rappresenta la mappa da usare per la difesa
    DefenseUnit defense_map_[kHeight][kWidth]; 
    // verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
    bool check_position(const Position& position) const; 
    // scrivo una nave nella matrice
    // inizio e fine devono già condividere la stessa riga o la stessa colonna in accordo con la direzione 
    // true se l'operazione è correttamente eseguibile
    bool place_ship(Position& init, Position& end, const Position& center_block, int block_dimension, Direction direction); 
    // verifico se la coordinata di centro specificata può essere una posizione plausibile per una nave di lunghezza 
    // length specificata e orientamento orientation.
    // ritorna true se la nave ricoprirebbe una regione non vuota o non rientra nella matrice
    bool check_area_for_placing(const Position& target_destination, int length, Direction orientation) const; 
    // funzione che pulisce tutte le caselle nella regione specificata: centro, lunghezza e direzione
    // le coordinate che andrà a pulire devono essere già testate come corrette!
    void clear_area(const Position& center_block, int length, Direction orientation); 
    // metodo che resetta tutt ala matrice di difesa
    void clear_defense_map(); 

}; 


#endif