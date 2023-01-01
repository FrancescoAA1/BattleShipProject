#include "SupportShip.h"

//Per eseguire la sua azione di spostamento e cura, la nave di supporto ha bisogno dei seguenti dati:
//La posizione obiettivo dello spostamento, anche centro dell'area di cura
//anche se la nave non necessita di attack unit fornite da terzi per eseguire la sua azione,
//viene comunque passato un array (vuoto) per conformare i metodi action di tutte le navi
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
void SupportShip::action(const Position& target, const std::vector<AttackUnit>& data) 
{
    defense_map().move_ship(this->centre(), target);
    defense_map().fix_ship(target);
}

/*    for(int i = -(kSide/2); i <= kSide/2; i++)
    {
        for(int j = -(kSide/2); j <= kSide/2; j++)
        {
            //controllo se l'unità che sto analizzando appartiene alla nave stessa;
            //in quel caso non devo procedere alla cura
            if(map.defense_map()[target.X() + i][target.Y() + j].block_center() != map.defense_map()[target.X()][target.Y()].block_center())
            {
                map.defense_map()[target.X() + i][target.Y() + j].heal();
            }
        }
    }    



//@TOASK il metodo action delle navi semplicemente aggiorna le mappe a livello visivo?

//metodo heal()
//da aggiungere a DefenseUnit

void heal()
{
    if(status_ == DefenseStatus::hit) status_ = DefenseStatus::taken ;
}
*/
