//Author: Francesco Fantin
#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{

    // Controllo del numero di parametri
    // Se sono più tre o quattro, si tratta di una funzionalità di replay

    if (argc == 4 && strcmp(argv[1], "f") == 0)
    {

        // scrittura su file del replay su un altro file
        // file da leggere
        std::string file_name = argv[2];
        // file su cui scrivere
        std::string output = argv[3];
        try
        {
            Game g{file_name, output};
            // inizio partita
            g.play_game();
        }
        catch (...)
        {
            std::cerr << "Errore durante la lettura del file: file di log corrotto o inesistente" << '\n';
        }
    }
    else if (argc == 3 && strcmp(argv[1], "v") == 0)
    {
        // stampa a video del file del replay
        // file da leggere
        std::string file_name = argv[2];
        try
        {
            Game g{file_name};
            // inizio partita
            g.play_game();
        }
        catch (...)
        {
            std::cerr << "Errore durante la lettura del file: file di log corrotto o inesistente" << '\n';
        }
    }
    else
    {
        std::cout << "Lista Parametri Errata!" << std::endl;
    }

    return 0;
}