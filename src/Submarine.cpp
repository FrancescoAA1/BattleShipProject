#include "Submarine.h"
#include <iostream>

// Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
// La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
// Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
// i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
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

// metodo per il debug
bool Submarine::action(const Position &target, const std::vector<AttackUnit> &data)
{
    if (data.empty())
    {
        std::cout << "Il sottomarino con centro " << this->centre() << " ha provato a eseguire l'azione ma il vettore di dati passato era vuoto (" << data.size() << ")\n";
        return false;
    }

    bool b = defense_map().move_ship(this->centre(), target);
    // sposto il sottomarino
    if (b)
    {

        Position start = centre() - Position{kSide / 2, kSide / 2};
        int count = 0;
        // inserisco per ogni casella Y se piena o unknown se vuota
        for (int i = 0; i < kSide; i++)
        {
            for (int j = 0; j < kSide; j++)
            {
                if (attack_grid_.check_position(start))
                {
                    if (count < data.size() && data[count] == AttackUnit::spotted)
                        attack_grid_.spot_position(start);

                    count++;
                }
                start.set_x(start.X() + 1);
            }
            start.set_y(start.Y() + 1);
            start.set_x(centre().X() - (kSide/2));
        }

        std::cout << "Il sottomarino con centro " << this->centre() << " ha eseguito l'azione con esito 1\n";
        std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
        return true;
    }

    // se arrivo qui significa che il movimento non era consentito
    std::cout << "Il sottomarino con centro " << this->centre() << " ha eseguito l'azione con esito 0, poiché il movimento verso " << target << " non era consentito";
    return false;
}
