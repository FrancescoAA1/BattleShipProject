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
        int counter = 0;

        for (int y = -kSide / 2; y <= kSide / 2; y++)
        {
            for (int x = -kSide / 2; x <= kSide / 2; x++)
            {
                // controllo se la posizione relativa nell'array rispetto al centro è valida, e se lo è procedo
                // a controllare il contenuto del vettore, altrimenti skippo e vado avanti
                Position t = Position(target.X() + x, target.Y() + y);
                if (this->attack_grid_.check_position(t))
                {
                    if (data[counter] == AttackUnit::spotted)
                        attack_grid_.spot_position(t);
                    counter++;
                }
            }
        }
        return true;
    }

    // se arrivo qui significa che il movimento non era consentito
    return false;
}
