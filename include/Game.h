// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_GAME_H_
#define BATTLESHIPPROJECT_GAME_H_

#include "GameMode.h"
#include "Player.h"
#include "RobotPlayer.h"
#include "HumanPlayer.h"
#include "FileWriter.h"
#include "Replay.h"
#include "Utility.h"
#include <string>
#include <typeinfo>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

class Game
{
public:

    static constexpr int kMaxRounds = 10000;

    // costruttore che accetta i nomi dei due giocatori, la modalità di gioco e il numero di round
    Game(const std::string &nickname_1, const std::string &nickname_2, GameMode mode, int nRounds, const std::string &file_name);

    // costruttore per la funzionalità di replay con stampa a video
    Game(const std::string &filename);

    // costruttore per la funzionalità di replay con scrittura su file
    Game(const std::string &filename, const std::string &output);

    // funzione che gioca un'intera partita
    void play_game();

    // funzione che gesitisce l'aggiunta delle navi da entrambi i giocatori
    void add();

    // funzione che aggiunge tutte le navi del singolo giocatore
    void add_player_ships(std::unique_ptr<Player> &p);

    // funzione che stabilisce il giocatore che inizia la partita
    void first_player();

    // funzione che simula un turno di gioco
    void playRound();

    // funzione che simula un turno di gioco
    void play_single_turn(std::unique_ptr<Player> &p, std::unique_ptr<Player> &opp);

    // funzione che controlla se l'utente ha inserito comandi di visualizzazione mappa.
    // In caso positivo, tale comando viene eseguito. Ritorna true se il comando era di
    // tipo grafico o se la mossa è da conseidare non valida ai fini del turno, false altrimenti
    bool check_graphic_cmd(std::unique_ptr<Player> &p, const Move &m);

    // funzione che gestisca la stampa degli output (video/file)
    // a seconda della modalità di gioco
    void handleOutput(const std::string &str);

    // funzione che decrementa il numero di round
    int round_terminated() { return numberOfRounds--; }

    // funzione che attesta se uno dei due giocatori ha vinto la partita
    // ritorna true se uno dei due giocatori ha vinto, false altrimenti
    bool Win();

    // metodo getter
    int get_rounds() { return numberOfRounds; }

private:
    // puntatori ai due player
    std::unique_ptr<Player> player_1;
    std::unique_ptr<Player> player_2;

    Replay replay;
    FileWriter fw;

    // costanti (numero di navi all'inizio del gioco)
    static constexpr int kIronclad = 3;
    static constexpr int kSupportShip = 3;
    static constexpr int kSubmarine = 2;

    // numero di turni
    int numberOfRounds;
    // modalità di gioco
    GameMode mode;
};

#endif