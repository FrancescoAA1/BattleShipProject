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

    // aggiunta di una nave
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A1 A3", 3));

    // controllo ulteriore aggiunta nave
    Ship *s = p.get_ship(Position{0, 1});
    std::cout << s->centre();
    std::cout << "\n\n" <<std::endl;

    // tester compulsivo aggiunta navi
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("C3 C7", 5));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("B1 B1", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("H1 B1", 1)); //coordinate senza senso
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A7 C7", 3));  //cella occupata
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A1 C1", 3)); // cella occupata
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("D1 H1", 5));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("G7 G7", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("C10 C10", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("B10 B10", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("D8 H8", 5));

    // tester creazione mossa
    Move m = p.get_move("B10 A6");
    std::cout << "\n\nTester Inserimento Mossa\nPosizione origine: " << std::endl;
    std::cout << m.origin() << std::endl;
    std::cout << "\nPosizione target: " << std::endl;
    std::cout << m.target() << std::endl;
    std::cout << "\nTipo di mossa: " << std::endl;
    std::cout << std::to_string(m.movetype()) << std::endl;

    //tester retrieve unit
    std::vector<AttackUnit> unit = p.retrieve_unit(m.target());

    // stampa unit (se mossa è attacco, 1 unit, se mossa è discover, <=25 unit, altrimenti 0)
    //std::vector<AttackUnit> unit = p.execute_move(m.target(), m.movetype());
    for (int i = 0; i < unit.size(); i++)
    {
        std::cout << "\n Unit " + std::to_string(i) + ": " << std::endl;
        std::cout << unit[i];
    }

    RobotPlayer r = RobotPlayer("ciao");
    // std::cout << r.convert_to_command(Position{1,11});
    // std::cout << r.convert_to_position("A1");

    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 1));
    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 1));
    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 5));
    // std::cout<<  "Ships:" << r.get_ships_left() <<std::endl;
    // r.get_move("");
    // r.get_ship(Position{0,1});

    // Game g{"c", "g", GameMode::ComputerVsComputer, 6};
    // g.add();
    return 0;
}