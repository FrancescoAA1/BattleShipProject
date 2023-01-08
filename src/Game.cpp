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
    // primo giocatore esegue il proprio turno
    std::cout << "\n"
              << player_1->nickname() << " inizia il proprio turno.\n";
    play_single_turn(player_1);
    std::cout << "\n"
              << player_1->nickname() << " Ha terminato il proprio turno.\n";

    // se il primo giocatore non ha vinto, si continua a giocare
    if (!Win())
    {
        // secondo giocatore esegue il proprio turno
        std::cout << "\n"
                  << player_2->nickname() << " inizia il proprio turno.\n";
        play_single_turn(player_2);
        std::cout << "\n"
                  << player_2->nickname() << " Ha terminato il proprio turno.\n";
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
            std::cout << "\n"
                      << p->nickname() << " Inserisci una mossa ";
            getline(std::cin, cmd_player_1);
        }
        // se il giocatore è un computer, la funzione get_move ignora
        // la stringa vuota passata come parametro e restituisce una mossa valida

        // se il giocatore è umano, get_move controlla il comando
        // passato come parametro, e restituendo una mossa
        m = p->get_move(cmd_player_1);

        // controllo comandi AA AA e YY YY //fallo anche eseguire
        if (m.check_for_graphic_cmd())
        {
            if (m.movetype() == MoveType::clearMap)
            {
                // da implementare
            }
            else if (m.movetype() == MoveType::showMap)
            {
                std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
            }
        }

        // nei casi menzionati sopra la mossa non è valida ai fini del turno
        if (m.movetype() != MoveType::invalid)
        {
            std::cout << "Mossa Effettuata: " << convert_to_command(m.origin()) << " " << convert_to_command(m.target()) << "\n"
                      << std::endl;
            std::vector<AttackUnit> units = p->execute_move(m.target(), m.movetype());
            p->handle_response(units, m);

            // if(mode == GameMode::ComputerVsComputer)
            // {
            //  std::cout << visual_merge_grid(this->attack_grid(), this->defense_map());
            // }
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
    std::cout << "\n"
              << player_1->nickname() << " Inizia Ad Aggiungere le tue NAVI!" << std::endl;

    // Aggiunta delle navi da parte del primo giocatore
    add_player_ships(player_1);
    std::cout << "\n"
              << player_2->nickname() << " Inizia Ad Aggiungere le tue NAVI!" << std::endl;
    // Aggiunta delle navi da parte del seconda giocatore
    add_player_ships(player_2);
    std::cout << "\nNumero navi " << player_1->nickname() << " dopo inserimento: " << std::to_string(player_1->get_ships_left()) << std::endl;
    std::cout << visual_merge_grid(player_1->attack_grid(), player_1->defense_map());
    std::cout << "\nNumero navi " << player_2->nickname() << " dopo inserimento: " << std::to_string(player_2->get_ships_left()) << "\n"
              << std::endl;
    std::cout << visual_merge_grid(player_2->attack_grid(), player_2->defense_map());
}

void Game::add_player_ships(Player *p)
{
    // variabili che indicano il numero di navi da inserire per ogni tipologia
    int nIronclad = kIronclad;
    int nSupport = kSupportShip;
    int nSubmarine = kSubmarine;

    std::string cmd_add;
    bool check;

    // per ogni tipo di nave, vengono aggiunte alla lista tante navi quante sono quelle definite dalle relative costanti
    while (nIronclad > 0)
    {
        // se l'input è effettuato da un giocatore umano, quest'ultimo deve inserire le coordinate delle navi
        // in caso di giocatore computer, le coordinate vengono generate randomicamente
        if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n"
                      << p->nickname() + " inserisci le coordinate della CORAZZATA\n";
            getline(std::cin, cmd_add);
        }

        check = p->add_ships(cmd_add, 5);
        if (check)
        {
            nIronclad--;
            if (nIronclad > 0)
            {
                // std::cout << "Corazzata Aggiunta! Ne mancano " << std::to_string(nIronclad) << std::endl;
                std::cout << ". Ne mancano " << std::to_string(nIronclad) << std::endl;
            }
            else
            {
                std::cout << ". Complimenti! Tutte le corazzate sono state aggiunte!\n"
                          << std::endl;
            }
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            // solo il giocatore umano (e non il PC) deve essere notificato dell'errore
            std::cout << "Coordinate Non Valide" << std::endl;
        }
    }

    while (nSupport > 0)
    {
        if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n"
                      << p->nickname() + " inserisci le coordinate della NAVE DI SUPPORTO\n";
            getline(std::cin, cmd_add);
        }
        check = p->add_ships(cmd_add, 3);
        if (check)
        {
            nSupport--;
            if (nSupport > 0)
            {
                // std::cout << "Nave di Supporto Aggiunta! Ne mancano " << std::to_string(nSupport) << std::endl;
                std::cout << ". Ne mancano " << std::to_string(nSupport) << std::endl;
            }
            else
            {
                std::cout << ". Complimenti! Tutte le Navi di Supporto sono state aggiunte!\n"
                          << std::endl;
            }
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "Coordinate Non Valide" << std::endl;
        }
    }

    while (nSubmarine > 0)
    {
        if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n"
                      << p->nickname() + " inserisci le coordinate del SOTTOMARINO\n";
            getline(std::cin, cmd_add);
        }
        check = p->add_ships(cmd_add, 1);
        if (check)
        {
            nSubmarine--;
            if (nSubmarine > 0)
            {
                // std::cout << "Sottomarino Aggiunto! Ne mancano " << std::to_string(nSubmarine) << std::endl;
                std::cout << ". Ne mancano " << std::to_string(nSubmarine) << std::endl;
            }
            else
            {
                std::cout << ". Complimenti! Tutti sottomarini sono stati aggiunti!\n"
                          << std::endl;
            }
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "Coordinate Non Valide" << std::endl;
        }
    }
}

Game::~Game()
{
    // elimino tutta la memoria allocata nell'heap
    delete player_1;
    delete player_2;
    player_1 = nullptr;
    player_2 = nullptr;
}
