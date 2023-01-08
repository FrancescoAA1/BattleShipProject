#include "Submarine.h"
#include <iostream>

//Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
//La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
//Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
/*bool Submarine::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() < kSide*kSide) return false;
    
    //sposto il sottomarino
    if(defense_map().move_ship(this->centre(), target))
    {
        int counter = 0;
        //data è un vettore che salva una matrice kSide * kSide salvata per righe
        for(int i = -kSide/2; i <= kSide/2; i++)
        {
            for(int j = -kSide/2; j <= kSide/2; j++)
            {
                
                if(data[counter++] == AttackUnit::spotted) attack_grid_.spot_position(target + Position(j, i));
            }
        }

        return true;
    } 

    //se arrivo qui significa che il movimento non era consentito
    return false;

    
}*/

//metodo per il debug
bool Submarine::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() < kSide*kSide)
    {
        std::cout << "Il sottomarino con centro " << this->centre() << " ha provato a eseguire l'azione ma il vettore di dati passato era troppo corto (" << data.size() << ")\n";
        return false;
    }
    
    bool b = defense_map().move_ship(this->centre(), target);
    //sposto il sottomarino
    if(b)
    {
        int counter = 0;
        //data è un vettore che salva una matrice kSide * kSide salvata per righe
        for(int i = -kSide/2; i <= kSide/2; i++)
        {
            for(int j = -kSide/2; j <= kSide/2; j++)
            {
                
                if(data[counter++] == AttackUnit::spotted) attack_grid_.spot_position(target + Position(j, i));
            }
        }
        std::cout << "Il sottomarino con centro " << this->centre() << " ha eseguito l'azione con esito 1\n";
        std::cout << visual_merge_grid(this->attack_grid(), this->defense_map()); 
        return true;
    } 

    //se arrivo qui significa che il movimento non era consentito
    std::cout << "Il sottomarino con centro " << this-> centre() << " ha eseguito l'azione con esito 0, poiché il movimento verso " << target << " non era consentito";
    return false;

    
}

