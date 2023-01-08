#ifndef BATTLESHIPPROJECT_SUBMARINE_H_
#define BATTLESHIPPROJECT_SUBMARINE_H_

#include "Ship.h"
#include "Utility.h"

class Submarine : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 1, dimensione = 1
        //non è necessario fornire l'orientamento in quanto la lunghezza è uno e sarebbe indifferente
        //l'orientamento verrà comunque impostato a un valore di default per completezza
        Submarine(Position& centre_position, DefenseMap& defense_map, AttackGrid& attack_grid) : Ship(kSize, kDefaultDirection, centre_position, defense_map, attack_grid) {}

        //ricordare l'override di action
        bool action(const Position& target, const std::vector<AttackUnit>& data) override;

        //costante che definisce la dimensione del sottomarino
        static constexpr int kSize = 1;

    private:

        //costante che definisce l'orientamento di default del sottomarino
        static constexpr Direction kDefaultDirection = Direction::horizontal;
        //costante che definisce il lato dell'area di mappa ispezionata
        //l'area ispezionata è un quadrato e la lunghezza del lato è dispari per permettere alla nave di essere al centro di essa
        static constexpr int kSide = 5;
}; 

/*
classe Submarine: rappresenta un sottomarino;
questa nave ha dimensione 1, e può eseguire una operazione di spostamento + ispezione della zona dove si è spostato
in un'area di 5 caselle * 5 caselle (ispezione = segna sulla mappa di attacco del giocatore le navi nemiche con una Y)
*/

#endif
