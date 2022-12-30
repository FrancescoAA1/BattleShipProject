#include "../include/Game.h"
#include <iostream>

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds)
{
    numberOfRounds = nRounds;
    mode = mode_;

    // da implementare scelta casuale del primo giocatore

    if (mode == GameMode::PlayerVsComputer)
    {
        // se la modalità di gioco è PlayerVsComputer uno dei due giocatori sarà umano
        HumanPlayer p = HumanPlayer(nickname_1);
        player_1 = &p;
    }
    else if (mode == GameMode::ComputerVsComputer)
    {
        // in modalità ComputerVsComputer entrambi i giocatori sono computer
        RobotPlayer p = RobotPlayer(nickname_1);
        player_1 = &p;
    }

    // in entrambe le modalità, uno dei due giocatori è un computer
    RobotPlayer p = RobotPlayer(nickname_2);
    player_2 = &p;
}

void Game::playRound()
{
    // inizio del turno del primo giocatore
    // la stringa sottostante conterrà la mossa del primo giocatore
    std::string cmd_player_1;

    // creazione di una mossa invalida tramite costruttore di default
    Move m;

    // il seguente ciclo viene ripetuto fintantochè il giocatore non inserisce una mossa valida
    // contraddistinta dal tipo di mossa
    do
    {
        // se la modalità è pc, il giocatore umano è tenuto ad inserire la propria mossa
        if (mode == GameMode::PlayerVsComputer)
        {
            std::cout << "Inserisci una mossa";
            std::cin >> cmd_player_1;
        }
        // se il giocatore è un computer, la funzione get_move ignora
        // la stringa vuota passata come parametro e restituisce una mossa valida

        // se il giocatore è umano, get_move controlla il comando
        // passato come parametro, e restituendo una mossa
        m = player_1->get_move(cmd_player_1);

        //controllo comandi AA AA e YY YY
        bool invalidCmd = player_1->check_for_graphic_cmd();

        //nei casi menzionati sopra la mossa non è valida ai fini del turno
        if (invalidCmd)
        {
            m.set_movetype(MoveType::invalid);
        }
        else
        {   //il secondo giocatore risponde alla mossa appena eseguita restituendo un vettore di attackUnits
            std::vector<AttackUnit> units = player_2->execute_move(m.target(), m.movetype());
            //il primo giocatore gestisce le unità ritornate dal secondo giocatore
            player_1->handle_response(units);
        }

    } while (m.movetype() == MoveType::invalid);

    //si controlla se il primo giocatore ha vinto
    if (!Win())
    {

        // inizio del turno del secondo giocatore
        //le procedure sono analoghe a quelle soprastanti
        // la stringa sottostante conterrà la mossa del secondo giocatore
        std::string cmd_player_2;

        // creazione di una mossa invalida tramite costruttore di default
        Move m2;

        do
        {
            // se la modalità è pc, il giocatore umano è tenuto ad inserire la propria mossa
            if (mode == GameMode::PlayerVsComputer)
            {
                std::cout << "Inserisci una mossa";
                std::cin >> cmd_player_2;
            }

            m2 = player_2->get_move(cmd_player_1);

            bool invalidCmd = player_2->check_for_graphic_cmd();

            if (invalidCmd)
            {
                m2.set_movetype(MoveType::invalid);
            }
            else
            {
                //il primo giocatore risponde alla mossa appena eseguita restituendo un vettore di attackUnits
                std::vector<AttackUnit> units = player_1->execute_move(m2.target(), m2.movetype());
                //il secondo giocatore gestisce le unità ritornate dal primo giocatore
                player_2->handle_response(units);
            }

        } while (m2.movetype() == MoveType::invalid);
    }
}

bool Game::Win()
{
    // se a player1 non rimangono navi, player2 ha vinto
    if (player_1->getShipsLeft() == 0)
    {
        std::cout << player_2->nickname() + "ha vinto!";
        return true;
    }
    // se a player2 non rimangono navi, player1 ha vinto
    else if (player_2->getShipsLeft() == 0)
    {
        std::cout << player_1->nickname() + "ha vinto!";
        return true;
    }
    // nessuno ha ancora vinto
    return false;
}
