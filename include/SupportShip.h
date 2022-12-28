#ifndef BATTLESHIPPROJECT_SUPPORTSHIP_H_
#define BATTLESHIPPROJECT_SUPPORTSHIP_H_

#include "Ship.h"

class SupportShip : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 3, dimensione = 3 e orientamento fornito
        SupportShip(Direction orientation) : Ship(kSize, orientation) {};

        //ricordare l'override di action

    private:

        //costante che definisce la dimensione della nave di supporto
        static constexpr int kSize = 3;
        //costante che definisce il lato dell'area di cura
        //l'area di cura è un quadrato e la lunghezza del lato è dispari per permettere alla nave di essere al centro dell'area
        static constexpr int kSide = 3;


}; 

#endif