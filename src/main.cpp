#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{

    // Controllo del numero di parametri
    // Se sono più di due, si tratta di una funzionalità di replay
    // Se sono due si tratta invece di una partita PlayerVsComputer
    // oppure ComputerVsComputer

    if (argc == 2)
    {
        // partita player vs computer
        if (strcmp(argv[1], "pc") == 0)
        {

            std::string name;
            std::cout << "Inserisci nome: ";
            std::cin >> name;

            std::cout << "Inserisci numero massimo di mosse: ";
            int nRounds;
            std::cin >> nRounds;

            std::string file_name;
            std::cout << "Inserisci nome del file di log: ";
            std::cin >> file_name;

            Game g{name, "Luca", GameMode::PlayerVsComputer, nRounds, file_name};
            g.play_game();
        }

        // partita computer vs computer
        else if (strcmp(argv[1], "cc") == 0)
        {
            std::cout << "Inserisci numero massimo di mosse: ";
            int nRounds;
            std::cin >> nRounds;

            std::string file_name;
            std::cout << "Inserisci nome del file di log: ";
            std::cin >> file_name;

            Game g{"Tomas", "Matteo", GameMode::ComputerVsComputer, nRounds, file_name};
            g.play_game();
        }
    }
    else
    {
        std::cout << "Lista Parametri Errata" << std::endl;
    }

    return 0;
}