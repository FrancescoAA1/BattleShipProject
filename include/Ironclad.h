#ifndef BATTLESHIPPROJECT_IRONCLAD_H_
#define BATTLESHIPPROJECT_IRONCLAD_H_

#include "Ship.h"

class Ironclad : public Ship 
{
    public:
        //costruttore
        //crea una nave con corazza = 5, dimensione = 5 e orientamento fornito
        Ironclad(Direction);

        //ricordare l'override di action

    private:

        //costante che definisce la dimensione della nave corazzata
        static constexpr int kSize = 5;
}; 

#endif
