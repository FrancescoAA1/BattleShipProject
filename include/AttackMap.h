#ifndef BATTLESHIPPROJECT_ATTACKMAP_H_
#define BATTLESHIPPROJECT_ATTACKMAP_H_

// Classe che rappresenta la mappa di attacco
// possiede una matrice di unità d'attacco e i metodi per verificarne 
// lo stato delle posizioni richieste 

#include "AttackUnit.h"
#include "Position.h"
#include <vector>
#include <ostream>

class AttackMap
{  
    public:

    // costruttore di default che setta tutto a vuoto
    AttackMap();  

    // Funzioni per l'ATTACCO: 

    // funzione che permette di impostare come spotted la posizione selezionata
    // aggiornando la mappa d'attacco
    // ritorna true se lo spot è andato a buon fine
    // lo spot fallisce se la cella non è vuota o non è valida
    bool spot_position(const Position& target_destination); 

    // imposta a hit la cella della mappa d'attacco di target specificato
    bool shot_position(const Position& target_destination, AttackUnit shot_status); 

    // Funzioni Utilitarie 

    // funzione che pulisce tutte le caselle nella matrice 
    void clear_area(); 

    // Overload dell'operatore << che scrive nell'output stream la matrice di difesa
    std::ostream& operator<<(std::ostream& data_stream); 

    private:    
    // Regione delle costanti da utilizzare nella classe  
    static constexpr int kHeight = 12; 
    static constexpr int kWidth = 12; 
    static constexpr char kHitAndFullSymbol = 'X'; 
    static constexpr char kHitAndEmptySymbol = 'O';
    static constexpr char kEmptySpace = ' '; 
    // rappresenta la mappa da usare per l'attacco
    AttackUnit attack_map_[kHeight][kWidth];  
    // verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
    bool check_position(const Position& position) const; 

}; 

#endif