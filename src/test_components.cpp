#include "../include/DefenseMap.h"
#include "../include/AttackGrid.h"
#include <iostream>

int main (void)
{
    DefenseMap def_map = DefenseMap(); 
    std::cout<<def_map; 

    AttackGrid test = AttackGrid(); 

    std::cout<<test; 
    return 0; 
}