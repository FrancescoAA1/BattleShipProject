#include "Ironclad.h"
#include <iostream>

//Per eseguire la sua azione di attacco, la nave corazzata ha bisogno dei seguenti dati:
//La mappa di attacco del giocatore che ordina la mossa, la quale verrà modificata
//La posizione obiettivo dell'attacco
//La nuova attack unit modificata da sostituire nella mappa di attacco ricevuta, alla posizione target 
//sebbene la attack unit da ricevere sia una sola, viene utilizzato un array per conformare i metodi action di tutte le navi
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
//ritorno comunque un booleano che conferma che l'azione è stata effettuata
/*bool Ironclad::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() > 0) return attack_grid_.shot_position(target, data[0]);
    else return false;
}*/

//metodo per il debug
bool Ironclad::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() > 0)
    {
        bool b = attack_grid_.shot_position(target, data[0]);
        std::cout << "La corazzata con centro " << this->centre() << " ha eseguito una mossa; esito del colpo: " << b << std::endl;
        std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        return b;
    }

    else 
    {
        std::cout << "La corazzata con centro " << this->centre() << " ha provato ad esguire una mossa ma il vettore di dati passato non era abbastanza lungo" << std::endl;
        std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        return false;
    }
}