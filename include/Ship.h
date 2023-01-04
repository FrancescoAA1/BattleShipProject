#ifndef BATTLESHIPPROJECT_SHIP_H_
#define BATTLESHIPPROJECT_SHIP_H_

#include <vector>
#include "Position.h"
#include "AttackUnit.h"
#include "Direction.h"
#include "AttackGrid.h"
#include "DefenseMap.h"

class Ship
{
    public:

        //disattivo il costruttore di copia per rendere la classe astratta
        Ship(const Ship&) = delete;
        //disattivo l'assegnamento di copia per rendere la classe astratta
        Ship& operator=(const Ship&) = delete;

        //metodo virtuale che definisce l'azione che può eseguire la nave (attacco, spostamento e cura, spostamento e ispezione)
        //e' necessario implementarlo in maniera diversa in ognuna della classi nave derivate
        //il vector di AttackUnit è un insieme di unità d'attacco fornite dal giocatore in difesa al giocatore in attacco
        //contiene unità di attacco aggiornate da sostituire nella mappa di attacco del giocatore attaccante
        //nel caso dell'azione di cura il vettore sarà vuoto
        //nel caso dell'azione di attacco il vettore conterrà solo una unità
        //nel caso dell'azione di ispezione il vettore conterrà 25 unità
        //viene comunque restituto un booleano per confermare il successo della mossa
        virtual bool action(const Position& target, const std::vector<AttackUnit>&) = 0;

        //metodi getter
        int armor() const {return armor_;}
        int size() const {return size_;}
        Position centre() const {return centre_;}
        Direction orientation() const {return orientation_;}
        AttackGrid attack_grid() const {return attack_grid_;}
        DefenseMap defense_map() const {return defense_map_;}

        //metodi setter
        void set_center(const Position& new_centre) {centre_ = new_centre;}
        
        //la nave è stata colpita: riduce la corazza di 1
        //restituisce true se la nave è appena stata affondata (serve per avvisare di rimuoverla dal dizionario)
        bool hit();
        //la nave è stata curata da una nave di supporto: ripristina la corazza al valore iniziale (che è size_)
        void restore() {armor_ = size_;};
        
        virtual ~Ship(); 

    protected:

        //costruttore, richiede la dimensione della nave, il suo orientamento, il suo centro, le mappe in cui è contenuta
        Ship(int, Direction, Position&, DefenseMap&, AttackGrid&);
    

    private:

        //variabile che definisce la direzione secondo cui è orientata la nave
        Direction orientation_;
        //variabile che indica la corazza attuale della nave
        int armor_;
        //variabile che definisce la dimensione della nave
        int size_;
        //variabile che indica il centro della nave
        Position centre_;
        //campo che contine un firerimento alla mappa di attacco di cui fa parte
        AttackGrid attack_grid_; 
        //campo che contine un rigferimento alla mappa di difesa di cui fa parte
        DefenseMap defense_map_; 
}; 

/*
Classe Ship: rappresenta una nave generica a disposizione del giocatore
La classe è astratta e da essa derivano 3 sotto-classi, una per ogni tipo di nave nel gioco
Il punto fondamentale della classe è il metodo action()
*/

#endif