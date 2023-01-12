#include "Submarine.h"
#include <iostream>

// Per eseguire la sua azione di spostamento e ispezione, il sottomarino ha bisogno dei seguenti dati:
// La posizione obiettivo dello spostamento, anche centro dell'area ispezionata
// Un vettore di AttackUnit, che contiene la porzione di mappa nemica che è stata ispezionata
//
// i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione

bool Submarine::action(const Position &target, const std::vector<AttackUnit> &data)
{
    if (data.empty())
    {

        return false;
    }

    bool allowed = defense_map_.move_ship(this->centre(), target);
    // sposto il sottomarino
    if (allowed)
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

        return true;
    }

    // se arrivo qui significa che il movimento non era consentito
    return false;
}
