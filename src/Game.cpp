#include "../include/Game.h"
#include "../include/Utility.h"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds, const std::string &file_name)
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

    //fw = FileWriter(file_name);
    replay = Replay(file_name);
}

Game::Game(const std::string &file)
{
    // apertura del file di log da cui effettuare lettura
    replay = Replay(file);
    replay.open_log();
    mode = GameMode::PrintReplay;

    // settaggio dei parametri per la partita
    // tramite i dati presenti nel file di log
    player_1 = new HumanPlayer(replay.get_first_player_name());
    player_2 = new HumanPlayer(replay.get_second_player_name());
    numberOfRounds = replay.get_number_of_rounds();
}

// ATTENZIONE! RIDUCIBILE
Game::Game(const std::string &file, const std::string &output)
{
    // apertura del file di log da cui effettuare lettura
    replay = Replay(file);
    replay.open_log();
    mode = GameMode::WriteReplay;

    // settaggio dei parametri per la partita
    // tramite i dati presenti nel file di log
    player_1 = new HumanPlayer(replay.get_first_player_name());
    player_2 = new HumanPlayer(replay.get_second_player_name());
    numberOfRounds = replay.get_number_of_rounds();

    // file in cui effettua la scrittura
    fw = FileWriter(output);
}

void Game::first_player()
{
    Player *temp;
    srand(time(NULL));
    int rand_starter = std::rand() % 2;

    if (rand_starter == 1)
    {
        temp = player_1;
        player_1 = player_2;
        player_2 = temp;
    }

    fw.write_line(player_1->nickname());
    fw.write_line(player_2->nickname());
    fw.write_line(std::to_string(numberOfRounds));
}

void Game::handleOutput(const std::string &state)
{
    if (mode == GameMode::WriteReplay)
        fw.write_line(state);
    else
        std::cout << state;
}

void Game::playRound()
{
    // primo giocatore esegue il proprio turno
    std::string state = "\n" + player_1->nickname() + " inizia il proprio turno.\n";

    handleOutput(state);

    play_single_turn(player_1, player_2);
    state = "\n" + player_1->nickname() + " ha terminato il proprio turno.\n";

    handleOutput(state);

    // se il primo giocatore non ha vinto, si continua a giocare
    if (!Win())
    {
        // secondo giocatore esegue il proprio turno
        std::string state = "\n" + player_2->nickname() + " inizia il proprio turno.\n";

        handleOutput(state);

        play_single_turn(player_2, player_1);
        state = "\n" + player_2->nickname() + " ha terminato il proprio turno.\n";

        handleOutput(state);
    }
}

void Game::play_single_turn(Player *p, Player *opp)
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
            if (typeid(HumanPlayer) == typeid(*p))
            {
                std::cout << "\n"
                          << p->nickname() << " Inserisci una mossa ";
                getline(std::cin, cmd_player_1);
            }
        }
        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
            {
                cmd_player_1 = replay.next();
            }
            if (mode == GameMode::PrintReplay)
            {
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
            }
        }
        // se il giocatore è un computer, la funzione get_move ignora
        // la stringa vuota passata come parametro e restituisce una mossa valida

        // se il giocatore è umano, get_move controlla il comando
        // passato come parametro, e restituendo una mossa
        m = p->get_move(cmd_player_1);

        // controllo comandi AA AA

        bool invalid_move = p->check_graphic_cmd(m);

        if (!invalid_move)
        {
            std::vector<AttackUnit> units = opp->execute_move(m.target(), m.movetype());
            bool action_done = p->handle_response(units, m);

            if (!action_done)
            {
                m.set_movetype(MoveType::invalid);
            }
            else
            {
                std::string note = "Mossa Effettuata: " + convert_to_command(m.origin()) + " " + convert_to_command(m.target()) + "\n";

                handleOutput(note);

                fw.write_line(m.to_string());

                if (mode == GameMode::WriteReplay)
                {
                    fw.write_line(visual_merge_grid(p->attack_grid(), p->defense_map()));
                }
                else
                {
                    std::cout
                        << visual_merge_grid(p->attack_grid(), p->defense_map());
                }
            }
        }

    } while (m.movetype() == MoveType::invalid);
}

void Game::play_game()
{
    if (mode != GameMode::PrintReplay || mode == GameMode::WriteReplay)
    {
        first_player();
    }
    add();

    while (get_rounds() > 0 && !Win())
    {
        playRound();
        round_terminated();
    }
    if (fw.flush_recording())
    {
        std::cout << "\nFile di log Salvato Correttamente";
    }
}

bool Game::Win()
{
    // se a player1 non rimangono navi, player2 ha vinto
    if (player_1->get_ships_left() == 0)
    {
        std::string winner = player_2->nickname() + "ha vinto!";
        handleOutput(winner);
        return true;
    }
    // se a player2 non rimangono navi, player1 ha vinto
    else if (player_2->get_ships_left() == 0)
    {
        std::string winner = player_1->nickname() + "ha vinto!";
        handleOutput(winner);
        return true;
    }
    // nessuno ha ancora vinto
    return false;
}

void Game::add()
{

    std::string message = "\n" + player_1->nickname() + " Inizia Ad Aggiungere le tue NAVI!\n";
    handleOutput(message);
    // Aggiunta delle navi da parte del primo giocatore
    add_player_ships(player_1);

    message = "\n" + player_2->nickname() + " Inizia Ad Aggiungere le tue NAVI!\n";
    handleOutput(message);
    // Aggiunta delle navi da parte del seconda giocatore
    add_player_ships(player_2);
}

void Game::add_player_ships(Player *p)
{
    // variabili che indicano il numero di navi da inserire per ogni tipologia
    int nIronclad = kIronclad;
    int nSupport = kSupportShip;
    int nSubmarine = kSubmarine;

    std::string cmd_add;
    bool check;

    std::string message;

    // per ogni tipo di nave, vengono aggiunte alla lista tante navi quante sono quelle definite dalle relative costanti
    while (nIronclad > 0)
    {
        // se l'input è effettuato da un giocatore umano, quest'ultimo deve inserire le coordinate delle navi
        // in caso di giocatore computer, le coordinate vengono generate randomicamente
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n" + p->nickname() + " Inserisci le coordinate della Corazzata! ";

            getline(std::cin, cmd_add);
        }
        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
            {
                cmd_add = replay.next();
            }
            if (mode == GameMode::PrintReplay)
            {
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
            }
        }

        check = p->add_ships(cmd_add, 5, fw);
        if (check)
        {
            nIronclad--;
            if (nIronclad > 0)
            {
                message = "Corazzata Aggiunta! Ne mancano " + std::to_string(nIronclad) + "\n";
                handleOutput(message);
            }
            else
            {
                message = "Complimenti! Tutte le corazzate sono state aggiunte!\n\n";
                handleOutput(message);
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
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            message = "\n" + p->nickname() + " Inserisci le coordinate della Nave di Supporto! ";
            handleOutput(message);
            getline(std::cin, cmd_add);
        }
        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
            {
                cmd_add = replay.next();
            }
            if (mode == GameMode::PrintReplay)
            {
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
            }
        }
        check = p->add_ships(cmd_add, 3, fw);
        if (check)
        {
            nSupport--;
            if (nSupport > 0)
            {
                message = "Nave di Supporto Aggiunta! Ne mancano " + std::to_string(nSupport) + "\n";
                handleOutput(message);
            }
            else
            {
                message = "Complimenti! Tutte le navi di supporto sono state aggiunte!\n\n";
                handleOutput(message);
            }
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "Coordinate Non Valide" << std::endl;
        }
    }

    while (nSubmarine > 0)
    {
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n" + p->nickname() + " Inserisci le coordinate del Sottomarino! ";

            getline(std::cin, cmd_add);
        }
        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
            {
                cmd_add = replay.next();
            }
            if (mode == GameMode::PrintReplay)
            {
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
            }
        }
        check = p->add_ships(cmd_add, 1, fw);
        if (check)
        {
            nSubmarine--;

            if (nSubmarine > 0)
            {
                message = "Sottomarino Aggiunto! Ne mancano " + std::to_string(nSubmarine) + "\n";
                handleOutput(message);
            }
            else
            {
                message = "Complimenti! Tutti i sottomarini sono stati aggiunti!\n";
                handleOutput(message);
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
