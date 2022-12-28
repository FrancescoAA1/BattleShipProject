#ifndef BATTLESHIPPROJECT_PLAYER_H_
#define BATTLESHIPPROJECT_PLAYER_H_

#include <string>
#include "Map.h"
#include "Move.h"



class Player
{
    public:

    // Eccezione che viene lanciata se la mossa creata non è valida
    class InvalidMove : public std::exception {}; 
    
    //metodo che a partire da un comando ricava la mossa che verrà effettuata dalla nave
    //La stringa viene manipolata per ricavare posizione di origine e posizione target
    //Se la stringa non è nel formato corretto viene ritornato null
    //altrimenti si cerca la posizione di orgine nel dizionario delle navi (disponibile presso la mappa)
    //Se non viene trovata una nave si ritorna null
    //Altrimenti viene istanziato un oggetto di tipo Move

    //La mossa verrà poi trasferita al controller e gestita in base al tipo di mossa
    //Ad eccezione della cura, il giocatore avversario ritornerà un vettore di Attack Unit
    //contenente le celle ispezionate (nel caso del sonar) oppure la cella da attaccare (corazzata)

    //funzione virtuale pura di cui effettuare l'override nelle classi derivate Human Player e Robot Player
    virtual Move get_move(const std::string&) = 0;

    //metodo che verifica se uno spostamento di un sottomarino o di una nave di supporto può
    //essere effettuato
    //la nave, una volta accertatasi che lo spostamento può essere effettuato, compierà la sua azione
    bool check_movement(const Move&);

    //metodo che ritorna 0 (cura),1 (attacco),25 (sonar) celle a seconda della tipologia di mossa effettuata
    std::vector<AttackUnit> retrieve_unit(const Move&);

    //metodi getter
    std::string nickname() {return nickname_;}

    //non è necessario metodo getter che ritorni puntatore alla nave
    //dato che il giocatore ottiene dalla mappa la nave interessata da un comanda
    //e invoca il metodo azione di quest'ultima per compiere una mossa

    protected:

    //costruttore dato il nome del giocatore
    Player(const std::string&);
        
    //nome del giocatore
    std::string nickname_;
    //insieme della mappa di attacco e di difesa del giocatore con metodi di gestione
    Map sea_map_;


}; 

#endif