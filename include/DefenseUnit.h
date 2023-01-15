//Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_DEFENSEUNIT_H_
#define BATTLESHIPPROJECT_DEFENSEUNIT_H_

#include "Position.h"
// Rappresenta lo stato di una cella della mappa
// se è empty => non c'è nessuna nave su di esso 
// se è hit => la nave su di essa presente è stat colpita
// se è taken => la posizione è occupata da una nave
enum DefenseStatus
{
    empty,
    hit, 
    taken
}; 

class DefenseUnit
{

    public: 
    //costruttore dei default che imposta la posizione del centro di riferimento a non valida 
    //e lo stato a vuoto 
    DefenseUnit(); 
    //contruttore con specifica parametri di costruzione
    DefenseUnit(DefenseStatus status, const Position& center_block_position); 

    //ottengo lo stato della cella 
    DefenseStatus status() const { return status_; }
    //imposto lo stato della cella a un valore indicato dal relativo enumeratore
    void set_status(DefenseStatus status);
    //pulisco la cella: imposto lo stato a empty e metto il centro ad una posizione invalida
    void clear(); 
    //ottengo il centro del blocco di riferimento
    Position block_center() const { return center_block_position_; }
    //imposto il centro di riferimento ad un determinato valore
    void set_block_center(const Position& position);  
    //ottengo la dimensione del blocco di appartenenza
    int full_block_dimension() const { return full_block_dimension_; } 
    //imposto il valore della dimensione del blocco di appartenenza
    void set_full_block_dimension(int full_block_dimension); 
    
    private: 

    DefenseStatus status_; 
    Position center_block_position_;
    int full_block_dimension_; 
    
}; 
//overload degli operatori di uguaglianza per la classe sopra definita
bool operator==(const DefenseUnit&, const DefenseUnit&); 
bool operator!=(const DefenseUnit&, const DefenseUnit&); 

/*
Classe Defense Unit: rappresenta una unità del campo di gioco. 
Essa possiede uno stato che permette di verificare se quella determinata cella
rappresenta una posizione occupata da una nave o una zona colpita di una nave.
Ogni unità mantiene un riferimento al centro del blocco complessivo di cui fa 
parte al fine di rendere le operazioni con la mappa più efficaci e ridurne la 
complessità di rappresentazione. 
Inolte una DefenseUnit possiede un intero che specifica la dimensione del blocco 
di cui fa parte, sempre nell'ottica di facilitare le operazioni di scrittura
*/
#endif