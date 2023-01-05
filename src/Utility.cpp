#include "../include/Utility.h"

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::string visual_merge_grid(const AttackGrid &attack_grid, const DefenseMap &defense_map)
{
    std::string map = defense_map.to_string();
    std::string grid = attack_grid.to_string();

    return ""; 
}