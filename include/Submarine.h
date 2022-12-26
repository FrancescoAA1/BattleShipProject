#ifndef BATTLESHIPPROJECT_SUBMARINE_H_
#define BATTLESHIPPROJECT_SUBMARINE_H_

#include "Ship.h"

class Submarine : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 1, dimensione = 1 e orientamento fornito
        Submarine(Direction);

        //ricordare l'override di action

    private:

        //costante che definisce la dimensione del sottomarino
        static constexpr int kSize = 1;
}; 

#endif
