#ifndef BATTLESHIPPROJECT_REPLAY_H_
#define BATTLESHIPPROJECT_REPLAY_H_

#include "Move.h"
#include "Utility.h"
#include <vector>

class Replay
{
public:
    // costruttore che accetta come parametro il nome del file di log:
    // se la classe viene creata per leggere da file aprirà file_name in lettura
    // altrimenti rappresneta il nome del file di log in cui scrivere
    Replay(std::string file_name);

    // funzione che permette di registrare una mossa nello storico
    // player_name è il nome del giocatore che l'ha effettuata
    void record_move(std::string player_name, const Move &move);

    // funzione che permette di salvare su file tutto lo sotrico registrato
    // ritorna true se il log è stato scritto -> il file che crea è quello che ha nome specificato
    // nel costruttore
    bool flush_recording();

private:
    // variabile che salva il nome del file da creare
    // essa contiene il path completo e se non esplicitamente indicato crea il file nella direcotry corrente
    // se il file è già presente lo elimina e ne crea uno nuovo
    std::string file_name_;
    // vettore in cui salvo tutto lo sotrico per poi farne il flush su file
    std::vector<std::string> recording_;

    // AREA DELLE CONSTANTI
    static constexpr char kMarker = ' ';
    static constexpr char kLineMarker = '\n';
};

// La presente classe ha lo scopo registrare tutte le mosse effettuate in una partita e salvarle in un file di log
// Inoltre viene progettata oltre che per scrivere lo storico di una partita anche per leggerlo e mostrare a video
// o su file il "replay" di essa

#endif