#ifndef BATTLESHIPPROJECT_ATTACKGRID_H_
#define BATTLESHIPPROJECT_ATTACKGRID_H_

// Classe che rappresenta la mappa di attacco
// possiede una matrice di unità d'attacco e i metodi per verificarne
// lo stato delle posizioni richieste

#include "AttackUnit.h"
#include "Position.h"
#include <vector>
#include <ostream>

class AttackGrid
{
public:
    // le costanti delle dimesnioni possono essere pubbliche e accessibili dall'estreno
    static constexpr int kHeight = 12;
    static constexpr int kWidth = 12;

    // costruttore di default che setta tutto a vuoto
    AttackGrid();

    // Funzioni per l'ATTACCO:

    // funzione che permette di impostare come spotted la posizione selezionata
    // aggiornando la mappa d'attacco
    // ritorna true se lo spot è andato a buon fine
    // lo spot fallisce se la cella non è vuota o non è valida
    bool spot_position(const Position &target_destination);

    // imposta al valore passato come parametro (shot_status) la cella della mappa d'attacco di target specificato
    // ritorna true se lo shot è andato a buon fine
    // lo spot fallisce se la cella non è vuota o non è valida
    bool shot_position(const Position &target_destination, AttackUnit shot_status);

    // Funzioni Utilitarie

    // funzione che pulisce tutte le caselle nella matrice
    void clear_area();

    // funzione che pulisce dalla matrice tutte le caselle impostate ad X
    void clear_all_full_and_hit();

    // funzione che pulisce dalla matrice tutte le caselle impostate ad O
    void clear_all_full_and_empty();

    // funzione che pulisce dalla matrice tutte le caselle impostate ad Y
    void clear_sonared();

    // funzione che scrive in una stringa la mappa
    std::string to_string() const;
    // verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
    bool check_position(const Position &position) const;

private:
    // Regione delle costanti da utilizzare nella classe
    static constexpr char kHitAndFullSymbol = 'X';
    static constexpr char kHitAndEmptySymbol = 'O';
    static constexpr char kSpottedSymbol = 'Y';
    static constexpr char kEmptySpace = ' ';
    static constexpr char kFirstRowLetter = 'A';
    static constexpr int kFirstColumnNumber = 1;
    // rappresenta la mappa da usare per l'attacco
    AttackUnit attack_grid_[kHeight][kWidth];

    // ATTACK GRID: è una classe che rappresenta una mappa di attacco e fornisce i metodi per individuare
    // e aggiornare lo stato delle caselle. Viene usata dalle navi per le funzioni di attacco e discover
    // del sottomarino.
};

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream &operator<<(std::ostream &data_stream, const AttackGrid &attack_grid);
#endif