#ifndef BATTLESHIPPROJECT_ATTACKUNIT_H_
#define BATTLESHIPPROJECT_ATTACKUNIT_H_

//Rappresenta una unità marina di una mappa d'attacco
//l'enumeratore ha lo scopo di definire se una determinata cella è stata: 
// attaccaata e in quella posizione è presente una nave => X => full_and_hit
// attaccata e in quella posizione non è presente una nave => O => empty_and_hit
// la cella non è stat soggetta ad attacchi => empty 
enum AttackUnit
{
    empty, 
    emty_and_hit, 
    full_and_hit
};

#endif