#ifndef BATTLESHIPPROJECT_SUPPORTSHIP_H_
#define BATTLESHIPPROJECT_SUPPORTSHIP_H_

#include "Ship.h"
#include <vector>

class SupportShip : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 3, dimensione = 3 e orientamento fornito
        SupportShip(Direction orientation, DefenseMap& defense_map, AttackMap& attack_map) : Ship(kSize, orientation, defense_map, attack_map) {}

        //ricordare l'override di action
        void action(const Position& target, const std::vector<AttackUnit>& data) override;

    private:

        //costante che definisce la dimensione della nave di supporto
        static constexpr int kSize = 3;
        //costante che definisce il lato dell'area di cura
        //l'area di cura è un quadrato e la lunghezza del lato è dispari per permettere alla nave di essere al centro dell'area
        static constexpr int kSide = 3;
        //dopo l'iperazione di spostamento salva in questo campo il centro delle navi riparate per permettere 
        // a chi ha la collezione di mantere aggiornato lo stato
        std::vector<Position> last_fixed_ship; 

}; 

#endif