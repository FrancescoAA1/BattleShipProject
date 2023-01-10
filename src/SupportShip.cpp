#include "SupportShip.h"
#include <iostream>

//Per eseguire la sua azione di spostamento e cura, la nave di supporto ha bisogno dei seguenti dati:
//La posizione obiettivo dello spostamento, anche centro dell'area di cura
//anche se la nave non necessita di attack unit fornite da terzi per eseguire la sua azione,
//viene comunque passato un array (vuoto) per conformare i metodi action di tutte le navi
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
//viene comunque ritornato un booleano che conferma che la mossa è stata effettuata
/*bool SupportShip::action(const Position& target, const std::vector<AttackUnit>& data) 
{
    if(defense_map_.move_ship(this->centre(), target))
    {
        last_fixed_ship = defense_map_.discovers_neighbors(target, kSide);
        
        for(int i = 0; i < last_fixed_ship.size(); i++)
        {
            //curo la nave, e se l'azione non è valida restituisco false
            if(!defense_map_.fix_ship(last_fixed_ship[i])) return false;
        } 
        

        return true;
    }

    //se arrivo qui significa che il movimento non era valido
    return false;    
    
}*/

bool SupportShip::action(const Position& target, const std::vector<AttackUnit>& data) 
{
    if(defense_map_.move_ship(this->centre(), target))
    {
        last_fixed_ship = defense_map_.discovers_neighbors(target, kSide);
        
        for(int i = 0; i < last_fixed_ship.size(); i++)
        {
            //curo la nave, e se l'azione non è valida restituisco false
            if(!defense_map_.fix_ship(last_fixed_ship[i]))
            {
                std::cout << "La nave di supporto con centro " << this->centre() << " ha eseguito l'azione con esito 0 perché l'azione di cura sulla nave di centro " << last_fixed_ship[i] << " non era valida\n";
                return false;
            }
        } 
        
        std::cout << "La nave di supporto con centro " << this->centre() << " ha eseguito l'azione con esito 1 e ha curato " << last_fixed_ship.size() << " navi\n";
        return true;
    }

    //se arrivo qui significa che il movimento non era valido
    std::cout << "La nave di supporto con centro " << this->centre() << " ha eseguito l'azione con esito 0 perché il movimento non era consentito\n"; 
    return false;    
    
}