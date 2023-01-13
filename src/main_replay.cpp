#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>

/*
int main()
{
    HumanPlayer p = HumanPlayer("Ciao");

    Position p1 = Position(3,12);
    //std::cout << p.convert_to_command(p1);
    std::string cmd = "A4";
    Position p2 = convert_to_position(cmd);
    //std::cout << p.convert_to_command(p1);
    std::cout << p.attack_grid();

    //AttackGrid f = AttackGrid();
    //std::cout << p.attack_grid();
}

*/
int main(int argc, char **argv)
{

    // Controllo del numero di parametri
    // Se sono più di due, si tratta di una funzionalità di replay
    // Se sono due si tratta invece di una partita PlayerVsComputer
    // oppure ComputerVsComputer

    if (argc == 4)
    {

        // scrittura su file del replay su un altro file
        std::string file_name = argv[2];
        std::string output = argv[3];

        Game g{file_name, output};
        g.play_game();
    }
    else if (argc == 3)
    {
        // stampa a video del file del replay
        std::string file_name = argv[2];

        Game g{file_name};
        g.play_game();
    }
    else
    {
        std::cout << "Lista Parametri Errata!" << std::endl;
    }

    return 0;
}