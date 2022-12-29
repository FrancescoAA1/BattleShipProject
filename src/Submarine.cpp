#include "Submarine.h"

//Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
//La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
//Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
void Submarine::action(const Position& target, const std::vector<AttackUnit>& data)
{
    defenseMap().move_ship(this->centre(), target); 
    attackMap().spot_position(data);
}

/*

    int y_diff = -(kSide/2);
    int x_diff = -(kSide/2);

    //il vettore contiene una matrice di unità, salvando le sue entrate a "S" (la prima riga da sinistra a destra, la seconda
    //riga da destra a sinistra, la terza da sinistra a destra ecc...)
    //per leggere il vettore come una matrice a S devo considerare i seguenti punti:
    //se il risultato (k) della divisione intera i/kSide è un numero pari, la riga va letta da sinistra a destra (x aumenta);
    //                                                      se è dispari, da destra a sinistra (x diminuisce)
    //il risultato della divisione intera i/kSide è l'indice della riga dell'elemento
    
*/