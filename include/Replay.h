#ifndef BATTLESHIPPROJECT_REPLAY_H_
#define BATTLESHIPPROJECT_REPLAY_H_

#include "Move.h"
#include "Utility.h"
#include <vector>
//#include <filesystem>
//namespace fs = std::__fs::filesystem;

class Replay
{

public:
    class InvalidOperation : std::exception
    {
    };
    // costruttore che accetta come parametro il nome del file di log:
    // se la classe viene creata per leggere da file aprirà file_name in lettura
    // altrimenti rappresneta il nome del file di log in cui scrivere
    Replay(std::string file_name);

    Replay();

    // funzione per impostare i due giocatori (scritti nell'ordine di parametro)
    // e il numero massimo di mosse che rappresentano l'header file da scrivere
    void record_header(std::string player1, std::string player2, int num_rounds);

    // funzione che permette di registrare una mossa nello storico
    // player_name è il nome del giocatore che l'ha effettuata
    void record_move(const Move &move);

    // funzione che carica in memoria (nel buffer_) il file di log con cui è stato
    // costruito l'oggetto
    bool open_log();

    // funzione che permette di ottenere il primo giocatore se si apre un file
    // di log e lo si vuole leggere
    // lancia eccezione se il file non è ancora stato caricato
    std::string get_first_player_name();

    // funzione che permette di ottenere il secondo giocatore se si apre un file
    // di log e lo si vuole leggere
    // lancia eccezione se il file non è ancora stato caricato
    std::string get_second_player_name();

    // funzione che permette di ottenere il # di round se si apre un file
    // di log e lo si vuole leggere
    // lancia eccezione se il file non è ancora stato caricato
    int get_number_of_rounds();

    // funzione che ritorna il numero di mosse rimanenti nel buffer
    int get_remaining_rounds(); 

    // verifica se è disponibile una mossa nel data buffer
    bool has_next();

    // funzione che permette di ottenere la possima mossa dello stream del data buffer
    // ritona un astringa da convertire a mossa
    std::string next();

    // funzione che permette di salvare su file tutto lo sotrico registrato
    // ritorna true se il log è stato scritto -> il file che crea è quello che ha nome specificato
    // nel costruttore
    bool flush_recording();

    // distruttore che involca il flush se non è stato effettuato 
    // già in precedenza 
    ~Replay();


private:
    // variabile che salva il nome del file da creare
    // essa contiene il path completo e se non esplicitamente indicato crea il file nella direcotry corrente
    // se il file è già presente lo elimina e ne crea uno nuovo
    std::string file_name_;
    // vettore in cui salvo tutto lo sotrico per poi farne il flush su file
    std::vector<std::string> buffer_;
    // prossima mossa da leggere
    int currentTransaction;
    // flag per il flush in distruzione
    bool recorded; 

    // AREA DELLE CONSTANTI
    static constexpr char kMarker = ' ';
    static constexpr char kLineMarker = '\n';
    static constexpr int kFirstPlayerPosition = 0;
    static constexpr int kSecondPlayerPosition = 1;
    static constexpr int kNumRoundsPosition = 2;
    static constexpr int kStartRounds = 3;
    // costante per il nome della cartella da creare nella directory corrente
    // se non già presente
    //const std::string kDirname = "log"; 
};

// La presente classe ha lo scopo registrare tutte le mosse effettuate in una partita e salvarle in un file di log
// Inoltre viene progettata oltre che per scrivere lo storico di una partita anche per leggerlo e mostrare a video
// o su file il "replay" di essa
// L aclasse crea il log nella sottodirecory log della corrente. La crea se non esiste

#endif