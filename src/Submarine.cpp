#include "Submarine.h"

//Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
//La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
//Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
bool Submarine::action(const Position& target, const std::vector<AttackUnit>& data)
{
    if(data.size() < kSide*kSide) return false;

    //sposto il sottomarino
    if(defense_map().move_ship(this->centre(), target))
    {
        //data è un vettore che salva una matrice kSide * kSide salvata per righe
        for(int i = -kSide/2; i < kSide/2; i++)
        {
            for(int j = -kSide/2; j < kSide/2; j++)
            {
                if(data[kSide*i + j] == AttackUnit::spotted) attack_grid_.spot_position(target + Position(i, j));
            }
        }

        return true;
    } 

    //se arrivo qui significa che il movimento non era consentito
    return false;

    
}

