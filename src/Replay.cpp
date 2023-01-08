#include "../include/Replay.h"
#include <fstream>

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

// funzione che permette di salvare su file tutto lo sotrico registrato
// ritorna true se il log è stato scritto -> il file che crea è quello che ha nome specificato
// nel costruttore
bool Replay::flush_recording()
{
    // se lo storico di registrazioni è vuoto allora ritorno false
    if (recording_.empty())
        return false;
    std::ofstream file; 
    // altrimenti scrivo tutti gli elementi di recording_
    try
    {
        file = std::ofstream(file_name_);
        
        for (int i = 0; i < recording_.size(); i++)
        {
            file << recording_[i]; 
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