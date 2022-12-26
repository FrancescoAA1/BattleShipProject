#ifndef BATTLESHIPPROJECT_SUBMARINE_H_
#define BATTLESHIPPROJECT_SUBMARINE_H_

#include "Ship.h"

class Submarine : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 1, dimensione = 1
        //non è necessario fornire l'orientamento in quanto la lunghezza è uno e sarebbe indifferente
        //l'orientamento verrà comunque impostato a un valore di default per completezza
        Submarine() : Ship(kSize, kDefaultDirection) {}

        //ricordare l'override di action

    private:

        //costante che definisce la dimensione del sottomarino
        static constexpr int kSize = 1;
        //costante che definisce l'orientamento di default del sottomarino
        static constexpr Direction kDefaultDirection = horizontal;
}; 

#endif
