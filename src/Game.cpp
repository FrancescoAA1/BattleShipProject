#include "../include/Game.h"
#include <iostream>

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds)
{
    numberOfRounds = nRounds;
    mode = mode_;

    //da implementare scelta casuale del primo giocatore


    if (mode == GameMode::PlayerVsComputer)
    {
        //se la modalità di gioco è PlayerVsComputer uno dei due giocatori sarà umano
        HumanPlayer p = HumanPlayer(nickname_1);
        player_1 = &p;
    }
    else if (mode == GameMode::ComputerVsComputer)
    {
        //in modalità ComputerVsComputer entrambi i giocatori sono computer
        RobotPlayer p = RobotPlayer(nickname_1);
        player_1 = &p;
    }

    //in entrambe le modalità, uno dei due giocatori è un computer
    RobotPlayer p = RobotPlayer(nickname_2);
    player_2 = &p;
}

void Game::playRound()
{
    //inizio del turno del primo giocatore
    //la stringa sottostante conterrà la mossa del primo giocatore
    std::string cmd_player_1;

    //creazione di una mossa invalida tramite costruttore di default
    Move m;

    //il seguente ciclo viene ripetuto fintantochè il giocatore non inserisce una mossa valida
    //contraddistinta dal tipo di mossa
    do
    {
        //se la modalità è pc, il giocatore umano è tenuto ad inserire la propria mossa
        if (mode == GameMode::PlayerVsComputer)
        {
            std::cout << "Inserisci una mossa";
            std::cin >> cmd_player_1;
        }
        //se il giocatore è un computer, la funzione get_move ignora
        //la stringa vuota passata come parametro e restituisce una mossa valida

        //se il giocatore è umano, get_move controlla il comando 
        //passato come parametro, e restituendo una mossa
        m = player_1->get_move(cmd_player_1);

        //mossa di pulizia della mappa
        if(m.movetype() == MoveType::clearMap)
        {
            //da implementare
            player_1->AttackGrid().clear_area();
            //non è considerata una mossa valida ai fini del turno
            m.set_movetype(MoveType::invalid);
        }
        //mossa di stampa della mappa
        else if(m.movetype() == MoveType::showMap)
        {
            //da implementare
            //std::cout << player_1->defenseMap();
            //std::cout << player_1->AttackGrid();
            //non è considerata una mossa valida ai fini del turno
            m.set_movetype(MoveType::invalid);
        }

    } while (m.movetype() == MoveType::invalid);

    std::vector<AttackUnit> units2;

    //viene individuata la nave (responsabile della mossa effettuata) del primo giocatore 
    Ship* s2 = player_1->get_ship(m.origin());

    //risposta del secondo giocatore alla mossa appena effettuata

    //effettuare 2 distinzioni: colpo d'accatto e spot del sottomarino
    // per lo spot sei a posto -> usi retrive unit
    // per lo shot invece definire: 
    // un metodo che riceve un colpo: usi mappa.receive_shot che ti ritorna un pair: (centro della nave colpita, stato del colpo)
    // se lo AttackUnit = X => mi preoccupo e guardo nella collezione la nave con quel centro e la colpisco (hit). 
    // ultimo controllo: se la corazza è finita la devo eliminare: rimuovere dal vettore + chiamare mappa.remove_ship
    // ritotrno l'attackUnit
    if(m.movetype() != MoveType::moveAndFix)
    {
        units2 = player_2->retrieve_unit(m.target(), m.movetype());
    }

    //la funzione action permette alla nave di aggiornare la mappa di attacco e/0 difesa
    //l'invocazione dipende dal tipo di nave a cui punta il puntatore
    s2->action(m.target(), units2);


    //inizio del turno del secondo giocatore
    //le procedure sono identiche a quelle eseguite per il primo giocatore
    std::string cmd_player_2;
    Move m2;

    do
    {
        if (mode == GameMode::PlayerVsComputer)
        {
            std::cout << "Inserisci una mossa";
            std::cin >> cmd_player_2;
        }

        m2 = player_2->get_move(cmd_player_2);

        if(m.movetype() == MoveType::clearMap)
        {
            //da implementare
            player_2->AttackGrid().clear_area();
            m2.set_movetype(MoveType::invalid);
        }
        else if(m2.movetype() == MoveType::showMap)
        {
            //da implementare
            //std::cout << player_2->defenseMap();
            //std::cout << player_2->AttackGrid();
            m2.set_movetype(MoveType::invalid);
        }

    } while (m2.movetype() == MoveType::invalid);

    std::vector<AttackUnit> units;
    Ship* s = player_2->get_ship(m2.origin());

    if(m2.movetype() != MoveType::moveAndFix)
    {
        units = player_1->retrieve_unit(m2.target(), m2.movetype());
    }

    s->action(m2.target(), units);
}

bool Game::Win()
{
    //se a player1 non rimangono navi, player2 ha vinto
    if(player_1->getShipsLeft() == 0)
    {
        std::cout << player_2->nickname() + "ha vinto!";
        return true;
    }
    //se a player2 non rimangono navi, player1 ha vinto
    else if(player_2->getShipsLeft() == 0)
    {
        std::cout << player_1->nickname() + "ha vinto!";
        return true;
    }
    //nessuno ha ancora vinto
    return false;
}

