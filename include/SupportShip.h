#ifndef BATTLESHIPPROJECT_SUPPORTSHIP_H_
#define BATTLESHIPPROJECT_SUPPORTSHIP_H_

#include "Ship.h"

class SupportShip : public Ship
{
    public:
        //costruttore
        //crea una nave con corazza = 3, dimensione = 3 e orientamento fornito
        SupportShip(Direction orientation, Position& centre_position, DefenseMap& defense_map, AttackGrid& attack_grid) : Ship(kSize, orientation, centre_position, defense_map, attack_grid) {}

        //ricordare l'override di action
        void action(const Position& target, const std::vector<AttackUnit>& data) override;
        
        //costante che definisce la dimensione della nave di supporto
        static constexpr int kSize = 3;

    private:

        //costante che definisce il lato dell'area di cura
        //l'area di cura è un quadrato e la lunghezza del lato è dispari per permettere alla nave di essere al centro dell'area
        static constexpr int kSide = 3;
        //dopo l'iperazione di spostamento salva in questo campo il centro delle navi riparate per permettere 
        // a chi ha la collezione di mantere aggiornato lo stato
        std::vector<Position> last_fixed_ship; 

}; 

/*
classe SupportShip: questa classe rappresenta la nave di supporto, di dimensione 3;
questa nave può eseguire l'operazione di spostamento + cura delle navi alleate in un'area 3x3
*/

#endif