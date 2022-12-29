#include "../include/Game.h"
#include <iostream>

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds)
{
    numberOfRounds = nRounds;
    mode = mode_;

    //da implementare scelta casuale del primo giocatore
    if (mode == GameMode::PlayerVsComputer)
    {
        HumanPlayer p = HumanPlayer(nickname_1);
        player_1 = &p;
    }
    else if (mode == GameMode::ComputerVsComputer)
    {
        RobotPlayer p = RobotPlayer(nickname_1);
        player_1 = &p;
    }

    RobotPlayer p = RobotPlayer(nickname_2);
    player_2 = &p;
}

void Game::playRound()
{
    //INIZIO MOSSA 1
    std::string cmd_player_1;
    Move m;

    do
    {
        if (mode == GameMode::PlayerVsComputer)
        {
            std::cout << "Inserisci una mossa";
            std::cin >> cmd_player_1;
        }

        m = player_1->get_move(cmd_player_1);

        if(m.movetype() == MoveType::clearMap)
        {
            //da implementare
            player_1->attackMap().clear_area();
            m.set_movetype(MoveType::invalid);
        }
        else if(m.movetype() == MoveType::showMap)
        {
            //da implementare
            //std::cout << player_1->defenseMap();
            //std::cout << player_1->attackMap();
            m.set_movetype(MoveType::invalid);
        }

    } while (m.movetype() == MoveType::invalid);

    std::vector<AttackUnit> units;
    Ship* s = player_1->get_ship(m.origin());

    if(m.movetype() == MoveType::moveAndFix)
    {
        units = player_2->retrieve_unit(m.target(), m.movetype());
    }

    s->action(m.target(), units);


    //INIZIO MOSSA 2
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
            player_2->attackMap().clear_area();
            m2.set_movetype(MoveType::invalid);
        }
        else if(m2.movetype() == MoveType::showMap)
        {
            //da implementare
            //std::cout << player_2->defenseMap();
            //std::cout << player_2->attackMap();
            m2.set_movetype(MoveType::invalid);
        }

    } while (m2.movetype() == MoveType::invalid);

    std::vector<AttackUnit> units;
    Ship* s = player_2->get_ship(m2.origin());

    if(m2.movetype() == MoveType::moveAndFix)
    {
        units = player_1->retrieve_unit(m2.target(), m2.movetype());
    }

    s->action(m2.target(), units);
}

bool Game::Win()
{
    if(player_1->getShipsLeft() == 0)
    {
        std::cout << player_1->nickname() + "ha vinto!";
        return true;
    }
    else if(player_2->getShipsLeft() == 0)
    {
        std::cout << player_2->nickname() + "ha vinto!";
        return true;
    }
    return false;
}

