#include "../include/HumanPlayer.h"
#include "../include/RobotPlayer.h"
#include "../include/Game.h"
#include "../include/Move.h"
#include <string>
#include <iostream>

int main()
{

    HumanPlayer p = HumanPlayer("ciao");
    // std::cout << p.convert_to_command(Position{1,11});
    // std::cout << p.convert_to_position("A1");
    // p.get_ships_left();
    std::cout << p.add_ships("A1 A3", 3);
    p.get_ship(Position{0,1});
    Move m = p.get_move("A2 A6");
    std::cout << m.origin() << std::endl;
    std::cout <<m.target() << std::endl;

    Move m1 = p.get_move("AA AA");
    std::cout << m1.origin() << std::endl;
    std::cout <<m1.target() << std::endl;


    


    RobotPlayer r = RobotPlayer("ciao");
    std::cout << r.convert_to_command(Position{1,11});
    std::cout << r.convert_to_position("A1");

    std::cout << r.add_ships("A1 A3", 3); 
    std::cout<<  "Ships:" << r.get_ships_left() <<std::endl;
    r.get_move("");
    r.get_ship(Position{0,1});

    Game g{"c", "g", GameMode::ComputerVsComputer, 6};
    g.add();
    return 0;
}