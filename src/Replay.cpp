#include "../include/Replay.h"
#include <fstream>

// costruttore che accetta come parametro il nome del file di log:
// se la classe viene creata per leggere da file aprirà file_name in lettura
// altrimenti rappresneta il nome del file di log in cui scrivere
Replay::Replay(std::string file_name)
{
    // inizializzo le variabili di classe
    file_name_ = file_name;
    buffer_ = std::vector<std::string>();
}

// funzione per impostare i due giocatori (scritti nell'ordine di parametro)
// e il numero massimo di mosse che rappresentano l'header file da scrivere
void Replay::record_header(std::string player1, std::string player2, int num_rounds)
{
    // se è già pieno ne creo uno nuovo per mantenere corretto lo standard di scrittura
    if (buffer_.size() != 0)
        buffer_ = std::vector<std::string>();

    buffer_.push_back(player1);
    buffer_.push_back(player2);
    buffer_.push_back(std::to_string(num_rounds));
}

// funzione che permette di registrare una mossa nello storico
// player_name è il nome del giocatore che l'ha effettuata
void Replay::record_move(const Move &move)
{
    buffer_.push_back(move.to_string());
}

// funzione che permette di salvare su file tutto lo sotrico registrato
// ritorna true se il log è stato scritto -> il file che crea è quello che ha nome specificato
// nel costruttore
bool Replay::flush_recording()
{
    // se lo storico di registrazioni è vuoto allora ritorno false
    if (buffer_.empty())
        return false;
    std::ofstream file;
    // altrimenti scrivo tutti gli elementi di recording_
    try
    {
        file = std::ofstream(file_name_);

        for (int i = 0; i < buffer_.size(); i++)
        {
            file << buffer_[i] << kLineMarker;
        }

        file.close();

        return true;
    }
    catch (const std::exception &e)
    {
        file.close();
        return false;
    }
    return false;
}

// funzione che carica in memoria (nel buffer_) il file di log con cui è stato
// costruito l'oggetto
bool Replay::open_log()
{
    // apro il file e leggo tutte le righe caricandole nel buffer

    // TODO TOMORRW
    currentTransaction = 0; 
}

// funzione che permette di ottenere il primo giocatore se si apre un file
// di log e lo si vuole leggere
// lancia eccezione se il file non è ancora stato caricato
std::string Replay::get_first_player_name()
{
    // se il buffer è vuoto allora il file non è stato caricato o è invalido
    if(buffer_.size() == 0) throw InvalidOperation(); 

    return buffer_[kFirstPlayerPosition]; 
}

// funzione che permette di ottenere il secondo giocatore se si apre un file
// di log e lo si vuole leggere
// lancia eccezione se il file non è ancora stato caricato
std::string Replay::get_second_player_name()
{
    // se il buffer è vuoto allora il file non è stato caricato o è invalido
    if(buffer_.size() == 0) throw InvalidOperation(); 

    return buffer_[kSecondPlayerPosition]; 
}

// funzione che permette di ottenere il # di round se si apre un file
// di log e lo si vuole leggere
// lancia eccezione se il file non è ancora stato caricato
int Replay::get_number_of_rounds()
{
    // se il buffer è vuoto allora il file non è stato caricato o è invalido

}

// verifica se è disponibile una mossa nel data buffer
bool Replay::has_next()
{
    return currentTransaction == buffer_.size() - 1; 
}

// funzione che permette di ottenere la possima mossa dello stream del data buffer
// ritona un astringa da convertire a mossa
std::string next();