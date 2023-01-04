#include "../include/DefenseMap.h"
#include "../include/AttackGrid.h"
#include <iostream>

int main(void)
{
    DefenseMap def_map = DefenseMap();
    std::cout << def_map.add_ship(Position{1, 1}, Position{1, 5}) << std::endl;
    std::cout << def_map.add_ship(Position{2, 2}, Position{3, 5}) << std::endl;
    std::cout << def_map.add_ship(Position{2, 2}, Position{4, 2}) << std::endl;
    std::cout << def_map.add_ship(Position{0, 0}, Position{0, 0}) << std::endl;
    std::cout << def_map.add_ship(Position{11, 11}, Position{11, 11}) << std::endl;
    std::cout << def_map.add_ship(Position{11, 8}, Position{11, 11}) << std::endl;
    std::cout << def_map.add_ship(Position{10, 11}, Position{10, 9}) << std::endl;
    def_map.receive_shot(Position{1, 4});
    std::pair<Position, AttackUnit> p = def_map.receive_shot(Position{3, 8});
    std::cout << p.first << std::endl
              << p.second << std::endl;
    std::cout << def_map;
    // test percorso chiuso
    std::cout << def_map.add_ship(Position{9, 7}, Position{9, 3}) << std::endl;
    std::cout << def_map.add_ship(Position{11, 7}, Position{11, 3}) << std::endl;
    std::cout<<def_map.add_ship(Position{10,7}, Position{10,7})<<std::endl;  
    std::cout<<def_map.add_ship(Position{10,3}, Position{10,3})<<std::endl;      
    std::cout<<def_map.move_ship(Position{10,10}, Position{10,9})<<std::endl;
    std::cout << def_map;
    /*
    AttackGrid test = AttackGrid();

    test.shot_position(Position{1, 1}, AttackUnit::full_and_hit);
    test.shot_position(Position{1, 2}, AttackUnit::empty_and_hit);
    test.shot_position(Position{1, 3}, AttackUnit::spotted);
    test.shot_position(Position{1, 4}, AttackUnit::unknown);
    test.shot_position(Position{25, 31}, AttackUnit::full_and_hit);
    for (int i = 0; i <= 10; i++)
    {
        test.shot_position(Position{i, 11}, AttackUnit::spotted);
    }

    test.spot_position(Position{11, 11});
    test.clear_area();
    std::cout << test.to_string();
    */
    return 0;
}