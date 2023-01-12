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

    // 1) Controllo del numero di parametri
    // Se sono più di due, si tratta di una funzionalità di replay (da implementare)
    // Se sono due ossia "./main" e "pc" (o "cc")
    // 2)Creazione di un oggetto di classe Game (vanno forniti due nickname,
    //  modalità giocata, numero di turni)
    // 2.1) Scelta casuale del giocatore che inizia
    // 3) Scelta delle navi --> viene invocato il metodo add(Player& p)
    // 4) FIntanto che uno dei due giocatori non vince continua a giocare round
    if (argc > 4)
    {
        return 0;
    }
    else
    {
        Game match;

        if (argc == 4)
        {
            // scrittura su file del replay
            std::string file_name = argv[2];
            match = Game(file_name);
            
        }
        else if (argc == 3)
        {
            // stampa a video del replay
            std::string file_name = argv[2];
            match = Game(file_name);
        }
        else if (argc == 2)
        {

            if (strcmp(argv[1], "pc") == 0)
            {

                std::string name;
                std::cout << "Inserisci nome";
                std::cin >> name;
                std::cout << "Inserisci numero massimo di mosse";
                int nRounds;
                std::cin >> nRounds;
                match = Game(name, "Player2", GameMode::PlayerVsComputer, nRounds, "Partita");
            }
            else if (strcmp(argv[1], "cc") == 0)
            {
                match = Game("Player1", "Player2", GameMode::ComputerVsComputer, Game::kRoundsComputer, "Partita");
            }
        }

        match.play_game();
    }

    return 0;
}