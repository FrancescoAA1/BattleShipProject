#include "../include/DefenseMap.h"
#include "../include/AttackGrid.h"
#include "../include/HumanPlayer.h"
#include <iostream>
#include <vector>

int main(void)
{
    HumanPlayer player = HumanPlayer("Picaciu");

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
    std::cout << def_map.add_ship(Position{10, 7}, Position{10, 7}) << std::endl;
    std::cout << def_map.add_ship(Position{10, 3}, Position{10, 3}) << std::endl;
    std::cout << def_map;
    std::cout << def_map.move_ship(Position{10, 10}, Position{10, 9}) << std::endl;
    std::cout << def_map.move_ship(Position{1, 3}, Position{6, 3}) << std::endl;
    std::cout << def_map.move_ship(Position{11, 11}, Position{11, 0}) << std::endl;
    std::cout << def_map;

    std::cout << def_map.move_ship(Position{3, 2}, Position{3, 4}) << std::endl;
    std::cout << def_map.move_ship(Position{3, 4}, Position{2, 4}) << std::endl;
    std::cout << def_map.move_ship(Position{2, 4}, Position{4, 4}) << std::endl;
    std::cout << def_map.move_ship(Position{4, 4}, Position{3, 4}) << std::endl;
    std::cout << def_map;
    std::cout << def_map.move_ship(Position{6, 3}, Position{6, 5}) << std::endl;
    std::cout << def_map.move_ship(Position{6, 5}, Position{6, 4}) << std::endl;
    std::cout << def_map;
    std::cout << def_map.remove_ship(Position{11, 0}) << std::endl;
    std::cout << def_map.remove_ship(Position{3, 9}) << std::endl;
    std::cout << def_map.remove_ship(Position{9, 5}) << std::endl;
    std::cout << def_map.add_ship(Position{9, 5}, Position{9, 5}) << std::endl;
    std::cout << def_map;
    std::cout << def_map.remove_ship(Position{3, 4}) << std::endl;
    std::cout << def_map;
    def_map.receive_shot(Position{6, 2});
    def_map.receive_shot(Position{6, 3});
    def_map.receive_shot(Position{6, 4});
    def_map.receive_shot(Position{6, 5});
    def_map.receive_shot(Position{6, 6});
    def_map.receive_shot(Position{10, 3});
    def_map.receive_shot(Position{11, 3});
    std::cout << def_map;
    std::cout << def_map.fix_ship(Position{6, 4}) << std::endl;
    std::cout << def_map.fix_ship(Position{10, 3}) << std::endl;
    std::cout << def_map;
    Position center{8,4}; 
    std::vector<Position> vett = def_map.discovers_neighbors(center, 3);
    std::cout << vett.size() << std::endl;

    for (int i = 0; i < vett.size(); i++)
    {
        std::cout << vett[i] << std::endl;
    }
    std::vector<AttackUnit> attacchi = def_map.spot_area(center, 5);
    std::cout<<attacchi.size()<<std::endl; 
    AttackGrid test = AttackGrid();
    Position start = center - Position{5 / 2, 5 / 2};
    int count = 0; 
    // inserisco per ogni casella Y se piena o unknown se vuota
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (test.check_position(start))
            {
                if (attacchi[count] == AttackUnit::spotted)
                    test.spot_position(start); 

                count++; 
            }
            start.set_x(start.X() + 1);
        }
        start.set_y(start.Y() + 1);
        start.set_x(center.X() - 5 / 2);
    }
    std::cout<<test; 
    /*
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