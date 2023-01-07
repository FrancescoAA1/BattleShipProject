#include "../include/Replay.h"

// costruttore che accetta come parametro il nome del file di log:
// se la classe viene creata per leggere da file aprirà file_name in lettura
// altrimenti rappresneta il nome del file di log in cui scrivere
Replay::Replay(std::string file_name)
{
    // inizializzo le variabili di classe
    file_name_ = file_name; 
    recording_ = std::vector<std::string>(); 
}

// funzione che permette di registrare una mossa nello storico
// player_name è il nome del giocatore che l'ha effettuata
void Replay::record_move(std::string player_name, const Move &move)
{
    recording_.push_back(move.to_string()); 
}