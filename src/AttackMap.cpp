#include "../include/AttackMap.h"

// costruttore di default che setta tutto a vuoto
AttackMap::AttackMap()
{
    // imposto tutte le celle 
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            attack_map_[i][j] = AttackUnit::empty; 
        }
    }
}