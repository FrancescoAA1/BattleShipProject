//Author: Mattia Galassi 
#ifndef BATTLESHIPPROJECT_FILEWRITER_H_
#define BATTLESHIPPROJECT_FILEWRITER_H_

#include <vector>
#include <string>

class FileWriter
{

public:
    // costruttore che accetta come parametro il nome del file dove scrivere:
    FileWriter(std::string file_name);

    FileWriter();

    // funzione che permette di scrivere nel buffer una stringa
    void write_line(std::string line);

    // funzione che permette di salvare su file tutto il buffer salvato
    // ritorna true se il file è stato scritto -> il file che crea è quello che ha nome specificato
    // nel costruttore
    // false se il processo non è andato a buon fine
    bool flush_recording();

    // distruttore che involca il flush se non è stato effettuato
    // già in precedenza
    ~FileWriter();

private:
    // variabile che salva il nome del file da creare
    // essa contiene il path completo e se non esplicitamente indicato crea il file nella direcotry corrente
    // se il file è già presente lo elimina e ne crea uno nuovo
    std::string file_name_;
    // vettore in cui salvo tutto lo sotrico per poi farne il flush su file
    std::vector<std::string> buffer_;

    // flag per il flush in distruzione
    bool recorded;

    static constexpr char kLineMarker = '\n';
};

// La presente classe ha lo scopo wrappare l'oggetto file e permettere la scrittura di una stringa su di esso
// il vero processo di scrittura su file viene eseguito durante il flush oer non mantenere la risolrsa per tutta le esecuzione del programma
// se l'oggetto viene distrutto senza mai aver invocato un flush lo effettua di default nel distruttore
#endif