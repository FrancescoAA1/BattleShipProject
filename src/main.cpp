#include "../include/Game.h"
#include "../include/AttackGrid.h"
#include <iostream>
#include <string.h>

int main()
{
    HumanPlayer p = HumanPlayer("Ciao");
    
    Position p1 = Position(3,12);
    //std::cout << p.convert_to_command(p1);
    std::string cmd = "A4";
    Position p2 = p.convert_to_position(cmd);
    //std::cout << p.convert_to_command(p1);
    std::cout << p.attack_grid();

    //AttackGrid f = AttackGrid();
    //std::cout << p.attack_grid();
}

/*
int main(int argc, char** argv)
{

    //1) Controllo del numero di parametri
    //Se sono più di due, si tratta di una funzionalità di replay (da implementare)
    //Se sono due ossia "./main" e "pc" (o "cc")
    //2)Creazione di un oggetto di classe Game (vanno forniti due nickname,
    // modalità giocata, numero di turni)
    //2.1) Scelta casuale del giocatore che inizia
    //3) Scelta delle navi --> viene invocato il metodo add(Player& p)
    //4) FIntanto che uno dei due giocatori non vince continua a giocare round
    if(argc > 4)
    {
        return 0;
    }
    if(argc == 4)
    {
        //scrittura su file replay
    }
    else if(argc == 3)
    {
        //modalità replay
    }
    else if(argc == 2)
    {
        GameMode gm;
        Game match;

        if(strcmp(argv[1],"pc") == 0)
        {
            gm = GameMode::PlayerVsComputer;
            std::string name;
            std::cout << "Inserisci nome";
            std::cin >> name;
            match = Game(name, "Player2", gm, -1);

        }
        else if(strcmp(argv[1],"cc") == 0)
        {
            gm = GameMode::ComputerVsComputer; 
            match = Game("Player1", "Player2", gm, Game::kRoundsComputer);
        }

        //funzione che richiama l'inizio
        //random_call_for_start()

        match.add();

        while(match.get_rounds() > 0 && !match.Win())
        {
            match.playRound();
            match.round_terminated();
        }
    }

    return 0;
}
*/