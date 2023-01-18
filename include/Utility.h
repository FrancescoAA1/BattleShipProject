//Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_UTILITY_H_
#define BATTLESHIPPROJECT_UTILITY_H_

#include "DefenseMap.h"
#include "AttackGrid.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

// file di funzioni utilitarie da usare in più parti differenti del progetto

// funzione per fare split di strighe su un determinato carattere
std::vector<std::string> splitstr(std::string str, std::string delim = " ");

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::string visual_merge_grid(const AttackGrid &attack_grid, const DefenseMap &defense_map);

// funzione che converte una coppia di coordinate (quindi una delle due parti dell'intero comando)
// in una posizione
Position convert_to_position(const std::string &coordinate);

// funzione che converte una posizione in una delle due parti del comando
std::string convert_to_command(const Position &position);

// funzione per avere un numero random in modo un po' più randomico tra 0 e range - 1
int get_random(int range);

// funzione che conta il numero di cifre di un numero
int count_digits(int n);

    // costante utile per le conversioni da comando a posizione e viceversa
    static constexpr int kDefaultCapitalAscii = 65;
#endif
/*
La classe Utility mette a disposizione metodi utilizzati da più classi e che non richiedono accesso a campi privati di queste ultime.
Per maggiori informazioni sui metodi, si vedano i commenti in Utility.h
*/