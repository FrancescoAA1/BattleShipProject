// Author: Francesco Fantin
#include "../include/Game.h"

Game::Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode_, int nRounds, const std::string &file_name)
{
    numberOfRounds = nRounds;
    mode = mode_;

    if (mode == GameMode::PlayerVsComputer)
    {
        // if the game mode is PlayerVsComputer, one of the two players will be human
        Player *p1 = new HumanPlayer(nickname_1);
        player_1 = std::unique_ptr<Player>(p1);
        p1 = nullptr;
    }
    else if (mode == GameMode::ComputerVsComputer)
    {
        // in ComputerVsComputer mode, both players are computers
        Player *p1 = new RobotPlayer(nickname_1);
        player_1 = std::unique_ptr<Player>(p1);
        p1 = nullptr;
    }

    // in both modes, one of the two players is a computer
    Player *p2 = new RobotPlayer(nickname_2);
    player_2 = std::unique_ptr<Player>(p2);
    p2 = nullptr;
    replay = Replay(file_name);
    status = GameStatus::Ongoing;
}

Game::Game(const std::string &file)
{
    // open the log file for reading
    replay = Replay(file);
    replay.open_log();
    // set the replay print mode
    mode = GameMode::PrintReplay;

    // set the game parameters from the log file
    Player *p1 = new HumanPlayer(replay.get_first_player_name());
    Player *p2 = new HumanPlayer(replay.get_second_player_name());
    player_1 = std::unique_ptr<Player>(p1);
    player_2 = std::unique_ptr<Player>(p2);
    p1 = nullptr;
    p2 = nullptr;
    numberOfRounds = replay.get_number_of_rounds();
    status = GameStatus::Ongoing;
}

Game::Game(const std::string &file, const std::string &output)
{
    // open the log file for reading
    replay = Replay(file);
    replay.open_log();
    mode = GameMode::WriteReplay;

    // set the game parameters from the log file
    Player *p1 = new HumanPlayer(replay.get_first_player_name());
    Player *p2 = new HumanPlayer(replay.get_second_player_name());
    player_1 = std::unique_ptr<Player>(p1);
    player_2 = std::unique_ptr<Player>(p2);
    p1 = nullptr;
    p2 = nullptr;

    numberOfRounds = replay.get_number_of_rounds();
    status = GameStatus::Ongoing;

    // file where to write
    fw = FileWriter(output);
}

void Game::play_game()
{
    // in case of reading from log file
    // the first player is already decided since the game
    // has already been played
    if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay)
    {
        first_player();
    }

    // add the ships
    add();

    // the game continues until the round limit is reached or one of the players wins
    while (get_rounds() > 0 && !Win())
    {
        playRound();
        // decrement the number of rounds
        round_terminated();
    }

    std::string winner;

    if (status == GameStatus::Player1Won)
    {
        winner = player_1->nickname() + " has won! \n";
        handleOutput(winner);
    }
    else if (status == GameStatus::Player2Won)
    {
        winner = player_2->nickname() + " has won! \n";
        handleOutput(winner);
    }
    else
    {
        winner = "Draw!";
        handleOutput(winner);
    }

    if (mode != GameMode::WriteReplay)
    {
        std::cout << "\nGame Over\n";
    }

    // save the buffer to file
    // if successful, the log file will be available
    // in the bin folder of the project
    if (fw.flush_recording())
    {
        std::cout << "\nLog file saved successfully" << std::endl;
    }
}

void Game::add()
{
    std::string message = "\n" + player_1->nickname() + " Start adding your SHIPS!\n";
    handleOutput(message);
    // Add ships for the first player
    add_player_ships(player_1);

    message = "\n" + player_2->nickname() + " Start adding your SHIPS!\n";
    handleOutput(message);
    // Add ships for the second player
    add_player_ships(player_2);
}

void Game::add_player_ships(std::unique_ptr<Player> &p)
{
    // variables indicating the number of ships to add for each type
    int nIronclad = kIronclad;
    int nSupport = kSupportShip;
    int nSubmarine = kSubmarine;

    std::string cmd_add;
    bool check;

    std::string message;

    // for each ship type, add as many ships as defined by constants
    while (nIronclad > 0)
    {
        // if input is from human, user enters coordinates
        // if computer, coordinates are generated randomly
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n" + p->nickname() + " Enter the coordinates for the Ironclad! ";
            getline(std::cin, cmd_add);
        }

        // in replay mode, coordinates are read from file
        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
            {
                cmd_add = replay.next();
            }
            if (mode == GameMode::PrintReplay)
            {
                // add a pause for readability
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
            }
        }

        // add ironclad according to command
        check = p->add_ships(cmd_add, Ironclad::kSize);
        if (check)
        {
            nIronclad--;
            if (nIronclad > 0)
            {
                message = "Ironclad added with command " + cmd_add + "! " + std::to_string(nIronclad) + " remaining\n";
                handleOutput(message);
            }
            else
            {
                message = "Ironclad added with command " + cmd_add + "! All ironclads added!\n\n";
                handleOutput(message);
            }
            // record move to log
            if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay)
                replay.record_move(cmd_add);
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
            {
                // this should not happen unless the file is corrupted
                throw Replay::IllegalFileLog();
            }
            std::cout << "Invalid coordinates" << std::endl;
        }
    }

    while (nSupport > 0)
    {
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            message = "\n" + p->nickname() + " Enter the coordinates for the Support Ship! ";
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

        check = p->add_ships(cmd_add, SupportShip::kSize);

        if (check)
        {
            nSupport--;
            if (nSupport > 0)
            {
                message = "Support Ship added with command " + cmd_add + "! " + std::to_string(nSupport) + " remaining\n";
                handleOutput(message);
            }
            else
            {
                message = "Support Ship added with command " + cmd_add + "! All support ships added!\n\n";
                handleOutput(message);
            }
            if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay)
                replay.record_move(cmd_add);
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
            {
                throw Replay::IllegalFileLog();
            }
            std::cout << "Invalid coordinates" << std::endl;
        }
    }

    while (nSubmarine > 0)
    {
        if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay && typeid(*p) == typeid(HumanPlayer))
        {
            std::cout << "\n" + p->nickname() + " Enter the coordinates for the Submarine! ";
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

        check = p->add_ships(cmd_add, Submarine::kSize);
        if (check)
        {
            nSubmarine--;
            if (nSubmarine > 0)
            {
                message = "Submarine added with command " + cmd_add + "! " + std::to_string(nSubmarine) + " remaining\n";
                handleOutput(message);
            }
            else
            {
                message = "Submarine added with command " + cmd_add + "! All submarines added!\n";
                handleOutput(message);
            }
            if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay)
                replay.record_move(cmd_add);
        }
        else if (typeid(*p) == typeid(HumanPlayer))
        {
            if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
            {
                throw Replay::IllegalFileLog();
            }
            std::cout << "Invalid coordinates" << std::endl;
        }
    }
}

void Game::first_player()
{
    Player *temp1;
    Player *temp2;
    srand(time(NULL));

    int rand_starter = std::rand() % 2;

    // if random number is 1, swap players to change starting order
    if (rand_starter == 1)
    {
        temp1 = player_1.release();
        temp2 = player_2.release();
        player_1 = std::unique_ptr<Player>(temp2);
        player_2 = std::unique_ptr<Player>(temp1);
        temp1 = nullptr;
        temp2 = nullptr;
    }

    // write header in the log file
    replay.record_header(player_1->nickname(), player_2->nickname(), numberOfRounds);
}

void Game::playRound()
{
    std::string state = "\n" + player_1->nickname() + " starts their turn.\n";
    handleOutput(state);

    play_single_turn(player_1, player_2);
    state = "\n" + player_1->nickname() + " finished their turn.\n";
    handleOutput(state);

    if (!Win())
    {
        std::string state = "\n" + player_2->nickname() + " starts their turn.\n";
        handleOutput(state);

        play_single_turn(player_2, player_1);
        state = "\n" + player_2->nickname() + " finished their turn.\n";
        handleOutput(state);
    }
}

void Game::play_single_turn(std::unique_ptr<Player> &p, std::unique_ptr<Player> &opp)
{
    std::string cmd_player_1;
    Move m; // default invalid move

    do
    {
        if (mode == GameMode::PlayerVsComputer && typeid(HumanPlayer) == typeid(*p))
        {
            std::cout << "\n" << p->nickname() << " Enter a move: ";
            getline(std::cin, cmd_player_1);
        }

        if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
        {
            if (replay.has_next())
                cmd_player_1 = replay.next();
            if (mode == GameMode::PrintReplay)
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        }

        m = p->get_move(cmd_player_1);
        bool invalid_move = check_graphic_cmd(p, m);

        if (!invalid_move)
        {
            std::vector<AttackUnit> units = opp->execute_move(m.target(), m.movetype());
            bool action_done = p->handle_response(units, m);

            if (!action_done)
            {
                m.set_movetype(MoveType::invalid);
                if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
                    throw Replay::IllegalFileLog();
            }
            else
            {
                std::string note = "Move performed: " + convert_to_command(m.origin()) + " " + convert_to_command(m.target()) + "\n";
                handleOutput(note);

                if (mode != GameMode::PrintReplay && mode != GameMode::WriteReplay)
                    replay.record_move(m);

                if (mode == GameMode::WriteReplay)
                    fw.write_line(visual_merge_grid(p->attack_grid(), p->defense_map()));
                else if (mode == GameMode::PrintReplay)
                    std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
            }
        }
        else
        {
            if (mode == GameMode::PrintReplay || mode == GameMode::WriteReplay)
                throw Replay::IllegalFileLog();
            m.set_movetype(MoveType::invalid);
        }

    } while (m.movetype() == MoveType::invalid);
}

bool Game::Win()
{
    if (player_1->get_ships_left() == 0)
    {
        status = GameStatus::Player2Won;
        return true;
    }
    else if (player_2->get_ships_left() == 0)
    {
        status = GameStatus::Player1Won;
        return true;
    }
    return false;
}

bool Game::check_graphic_cmd(std::unique_ptr<Player> &p, const Move &m)
{
    if (m.movetype() != MoveType::invalid)
    {
        if (m.movetype() == MoveType::clearSonared)
        {
            p->attack_grid().clear_sonared();
            std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
        }
        else if (m.movetype() == MoveType::clearFullHit)
        {
            p->attack_grid().clear_all_full_and_hit();
            std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
        }
        else if (m.movetype() == MoveType::clearEmptyHit)
        {
            p->attack_grid().clear_all_full_and_empty();
            std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
        }
        else if (m.movetype() == MoveType::showMap)
        {
            std::cout << visual_merge_grid(p->attack_grid(), p->defense_map());
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }

    return true;
}

void Game::handleOutput(const std::string &state)
{
    if (mode == GameMode::WriteReplay)
        fw.write_line(state);
    else
        std::cout << state;
}
