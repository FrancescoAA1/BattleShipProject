#include "Submarine.h"

//Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
//La mappa di attacco del giocatore che ordina la mossa, la quale verrà modificata
//La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
//Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
void Submarine::action(Map& map, const Position& target, const std::vector<AttackUnit>& data)
{
    map.move_ship(?, target); //? sta per "non so quel dato"
    map.spot_positions(data);
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
    //
    //devo comunque lavorare con coordinate relative alla posizione del sottomarino (target), quindi uso le variabili
    //x_diff e y_diff che oscillano tra -kSide/2 e +kSide/2
    for(int i = 0; i < data.size(); i++)
    {
        int k = i/kSide;
        if(k % 2 == 0)      //controllo k pari
        {
            x_diff++ ;
            map.attack_map()[target.X() + x_diff][target.Y() + y_diff + k] = data[i];
        }
        else                //altrimenti k dispari
        {
            x_diff-- ;
            map.attack_map()[target.X() + x_diff][target.Y() + y_diff + k] = data[i];
        }
    }
}
*/