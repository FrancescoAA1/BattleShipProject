#ifndef BATTLESHIPPROJECT_UTILITY_H_
#define BATTLESHIPPROJECT_UTILITY_H_

#include "DefenseMap.h"
#include "AttackGrid.h"
// file di funzioni utilitarie da usare in più parti differenti del progetto

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::string visual_merge_grid(const AttackGrid& attack_grid, const DefenseMap& defense_map); 

#endif