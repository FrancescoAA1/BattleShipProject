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
std::string visual_merge_grid(const AttackGrid& attack_grid, const DefenseMap& defense_map);

// funzione che permette di convertire una posizione in una stringa che la rappresenta per la mappa
std::string convert_to_visual_position(const Position& position); 

//funzione per avere un numero random in modo un po' più randomico tra 0 e range - 1
int get_random(int range);

// costante utile per le conversioni da comando a posizione e viceversa
static constexpr int kDefaultCapitalAscii = 65;
#endif