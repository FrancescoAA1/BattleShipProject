#ifndef BATTLESHIPPROJECT_UTILITY_H_
#define BATTLESHIPPROJECT_UTILITY_H_

#include "DefenseMap.h"
#include "AttackGrid.h"
#include <vector>
// file di funzioni utilitarie da usare in più parti differenti del progetto

// funzione per fare split di strighe su un determinato carattere 
std::vector<std::string> splitstr(std::string str, std::string delim = " "); 

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::string visual_merge_grid(const AttackGrid& attack_grid, const DefenseMap& defense_map);

// funzione che permette di convertire una posizione in una stringa che la rappresneta per al mappa
std::string convert_to_visual_position(const Position& position); 

// costante utile per le conversioni da comando a posizione e viceversa
static constexpr int kDefaultCapitalAscii = 65;
#endif