#include "../include/Game.h"
#include "../include/Utility.h"
#include <iostream>

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds)
{
    numberOfRounds = nRounds;
    mode = mode_;

    // da implementare scelta casuale del primo giocatore

    if (mode == GameMode::PlayerVsComputer)
    {
        // se la modalità di gioco è PlayerVsComputer uno dei due giocatori sarà umano
        player_1 = new HumanPlayer(nickname_1);
        // player_1 = &p;
    }
    else if (mode == GameMode::ComputerVsComputer)
    {
        // in modalità ComputerVsComputer entrambi i giocatori sono computer
        player_1 = new RobotPlayer(nickname_1);
        // player_1 = &p;
    }

    // in entrambe le modalità, uno dei due giocatori è un computer
    player_2 = new RobotPlayer(nickname_2);
    // player_2 = &p;
}

Game::Game()
{
}

void Game::playRound()
{
    play_single_turn(player_1);

    if (!Win())
    {
        play_single_turn(player_2);
    }
}

void Game::play_single_turn(Player *p)
{
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
        m = p->get_move(cmd_player_1);

        // controllo comandi AA AA e YY YY //fallo anche eseguire
        if (p->check_for_graphic_cmd(m))
        {
            if (m.movetype() == MoveType::clearMap)
            {
                // da implementare
            }
            else if (m.movetype() == MoveType::showMap)
            {
                std::cout<<visual_merge_grid(p->attack_grid(), p->defense_map());
            }
        }

        // nei casi menzionati sopra la mossa non è valida ai fini del turno
        if (m.movetype() != MoveType::invalid)
        {
            std::vector<AttackUnit> units = p->execute_move(m.target(), m.movetype());
            p->handle_response(units, m);
        }

    } while (m.movetype() == MoveType::invalid);
}

bool Game::Win()
{
    // se a player1 non rimangono navi, player2 ha vinto
    if (player_1->get_ships_left() == 0)
    {
        std::cout << player_2->nickname() + "ha vinto!";
        return true;
    }
    // se a player2 non rimangono navi, player1 ha vinto
    else if (player_2->get_ships_left() == 0)
    {
        std::cout << player_1->nickname() + "ha vinto!";
        return true;
    }
    // nessuno ha ancora vinto
    return false;
}

void Game::add()
{
    add_player_ships(player_1);
    // add_player_ships(player_2);
}

void Game::add_player_ships(Player *p)
{
    int nIronclad = kIronclad;
    int nSupport = kSupportShip;
    int nSubmarine = kSubmarine;
    std::cout << "SOno QUi";

    std::string cmd_add;
    bool check;

    while (nIronclad > 0)
    {
        // if (typeid(*p) == typeid(HumanPlayer))
        // {
        //     std::cout << p->nickname() + " inserisci le coordinate della CORAZZATA";
        //     std::cin >> cmd_add;
        // }

        check = p->add_ships(cmd_add, 5);
        if (check)
        {
            nIronclad--;
        }
    }

    // while (nSupport > 0)
    // {
    //     if (typeid(*p) == typeid(HumanPlayer))
    //     {
    //         std::cout << p->nickname() + " inserisci le coordinate della NAVE DI SUPPORTO";
    //         std::cin >> cmd_add;
    //     }
    //     check = p->add_ships(cmd_add, 3);
    //     if (check)
    //     {
    //         nSupport--;
    //     }
    // }

    // while (nSubmarine > 0)
    // {
    //     if (typeid(*p) == typeid(HumanPlayer))
    //     {
    //         std::cout << p->nickname() + " inserisci le coordinate del SOTTOMARINO";
    //         std::cin >> cmd_add;
    //     }
    //     check = p->add_ships(cmd_add, 1);
    //     if (check)
    //     {
    //         nSubmarine--;
    //     }
    // }
}

Game::~Game()
{
    // elimino tutta la memoria allocata nell'heap
    delete player_1;
    delete player_2;
    player_1 = nullptr;
    player_2 = nullptr;
}
