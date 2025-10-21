// Author: Mattia Galassi 
#ifndef BATTLESHIPPROJECT_ATTACKUNIT_H_
#define BATTLESHIPPROJECT_ATTACKUNIT_H_

// Represents a naval unit in an attack map
// The enumerator defines the status of a cell:
// Attacked and a ship is present in that position => X => full_and_hit
// Attacked and no ship is present in that position => O => empty_and_hit
// The cell has not been subjected to attacks => unknown
enum AttackUnit
{
    unknown, 
    empty_and_hit, // O
    full_and_hit,  // X
    spotted        // Y
};

#endif
