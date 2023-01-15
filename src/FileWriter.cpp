//Author: Mattia Galassi
#include "../include/FileWriter.h"
#include <fstream>

// costruttore che accetta come parametro il nome del file dove scrivere:
FileWriter::FileWriter(std::string file_name)
{
    file_name_ = file_name;
    recorded = false;
    buffer_ = std::vector<std::string>();
}

FileWriter::FileWriter()
{
    file_name_ = ".txt";
    recorded = false;
    buffer_ = std::vector<std::string>();
}

// funzione che permette di scrivere nel buffer una stringa
void FileWriter::write_line(std::string line)
{
    buffer_.push_back(line);
}

// funzione che permette di salvare su file tutto il buffer salvato
// ritorna true se il file è stato scritto -> il file che crea è quello che ha nome specificato
// nel costruttore
// false se il processo non è andato a buon fine
bool FileWriter::flush_recording()
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

        recorded = true;

        return true;
    }
    catch (const std::exception &e)
    {
        file.close();
        return false;
    }
    return false;
}

// distruttore che involca il flush se non è stato effettuato
// già in precedenza
FileWriter::~FileWriter()
{
    if (!recorded && !buffer_.empty())
        flush_recording();
}