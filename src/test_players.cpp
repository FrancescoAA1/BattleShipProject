#include "../include/HumanPlayer.h"
#include "../include/RobotPlayer.h"
#include "../include/Game.h"
#include "../include/Move.h"
#include "../include/Utility.h"
#include <string>
#include <iostream>

int main()
{
    AttackGrid a = AttackGrid(); 
    DefenseMap d = DefenseMap(); 
    std::cout<<visual_merge_grid(a,d); 
    /*
    HumanPlayer p = HumanPlayer("ciao");
    
    //tester conversioni
    std::cout << "\nPosition convertita in comando: " << p.convert_to_command(Position{1,11});
    std::cout << "\nComando convertito in posizione: " <<p.convert_to_position("A1");


    // aggiunta di una nave
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A1 A3", 3));

    // controllo ulteriore aggiunta nave
    Ship *s = p.get_ship(Position{0, 1});
    std::cout << s->centre();
    std::cout << "\n\n"
              << std::endl;

    // tester compulsivo aggiunta navi
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("C3 C7", 5));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("B1 B1", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("H1 B1", 1)); // coordinate senza senso
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A7 C7", 3)); // cella occupata
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("A1 C1", 3)); // cella occupata
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("D1 H1", 5));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("G7 G7", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("C10 C10", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("B10 B10", 1));
    std::cout << "\nAggiunta nave " + std::to_string(p.add_ships("D8 H8", 5));

    std::cout << "\nNumero navi dopo inserimento: " << p.get_ships_left();

    // tester creazione mossa
    Move m = p.get_move("B10 A1");
    std::cout << "\n\nTester Inserimento Mossa\nPosizione origine: " << std::endl;
    std::cout << m.origin() << std::endl;
    std::cout << "\nPosizione target: " << std::endl;
    std::cout << m.target() << std::endl;
    std::cout << "\nTipo di mossa: " << std::endl;
    std::cout << std::to_string(m.movetype()) << std::endl;

    // tester retrieve unit
    std::vector<AttackUnit> unit = p.retrieve_unit(m.target());

    // stampa unit (se mossa è attacco, 1 unit, se mossa è discover, <=25 unit, altrimenti 0)
    // std::vector<AttackUnit> unit = p.execute_move(m.target(), m.movetype());
    for (int i = 0; i < unit.size(); i++)
    {
        std::cout << "\n Unit " + std::to_string(i) + ": ";
        std::cout << unit[i];
    }

    // tester receiveattack: affondo una nave
    p.receive_attack(m.target());
    Move m1 = p.get_move("B10 A2");
    p.receive_attack(m1.target());
    Move m2 = p.get_move("B10 A3");
    AttackUnit uni = p.receive_attack(m2.target());
    std::cout << std::to_string(uni);

    std::cout << "\nNumero navi dopo rimozione: " << p.get_ships_left();

    // tester execute move
    Move m3 = p.get_move("B10 H1");
    std::vector<AttackUnit> u = p.execute_move(m3.target(), m3.movetype());

    // tester handleResponse
    p.handle_response(u, m3);

    RobotPlayer r = RobotPlayer("ciao");
    std::cout << "\nPosition convertita in comando: " << p.convert_to_command(Position{1,11});
    std::cout << "\nComando convertito in posizione: " <<p.convert_to_position("A1");

    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 1));
    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 1));
    std::cout << "\nAggiunta nave casuale" + std::to_string(r.add_ships("", 5));
    
    std::cout << "\nNumero navi dopo inserimento: " << r.get_ships_left();
    // r.get_move("");
    r.get_ship(Position{0,1});

    // tester creazione mossa
    Move m4 = r.get_move("");
    std::cout << "\n\nTester Inserimento Mossa\nPosizione origine: " << std::endl;
    std::cout << m4.origin() << std::endl;
    std::cout << "\nPosizione target: " << std::endl;
    std::cout << m4.target() << std::endl;
    std::cout << "\nTipo di mossa: " << std::endl;
    std::cout << std::to_string(m4.movetype()) << std::endl;

    // tester retrieve unit
    std::vector<AttackUnit> units_r = r.retrieve_unit(m4.target());

    // stampa unit (se mossa è attacco, 1 unit, se mossa è discover, <=25 unit, altrimenti 0)
    // std::vector<AttackUnit> unit = p.execute_move(m.target(), m.movetype());
    for (int i = 0; i < units_r.size(); i++)
    {
        std::cout << "\n Unit " + std::to_string(i) + ": ";
        std::cout << units_r[i];
    }

    // tester receiveattack
    //r.receive_attack(m4.target());
    Move mr = r.get_move("");
    // r.receive_attack(mr.target());
    // Move mr1 = r.get_move("");
    // AttackUnit un = r.receive_attack(mr1.target());
    // std::cout << std::to_string(un);

    std::cout << "\nNumero navi dopo rimozione: " << r.get_ships_left();

    // Game g{"c", "g", GameMode::ComputerVsComputer, 6};
    // g.add(); */
    return 0;
}