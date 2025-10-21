// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_MOVE_H_
#define BATTLESHIPPROJECT_MOVE_H_

#include <string>
#include "Position.h"
#include "Utility.h"

// Enumerator that indicates the type of move performed by the player
enum MoveType{
    invalid,
    attack,          // attack (ironclad)
    moveAndFix,      // move and repair (support ship)
    moveAndDiscover, // move and inspect (submarine)
    showMap,         // display the player's maps
    clearEmptyHit,   // remove 'O' symbols from the player's map
    clearFullHit,    // remove 'X' symbols from the player's map
    clearSonared     // remove 'Y' symbols from the player's map
};

class Move
{
public:
    // Constructor valid for both Human and Robot Players
    Move(const Position&, const Position&, MoveType);

    // Constructor that creates an invalid move
    Move();

    // Getter methods
    Position origin() const { return origin_; }
    Position target() const { return target_; }
    MoveType movetype() const { return move_; }

    // Setter methods
    void set_movetype(MoveType m) { move_ = m; }
    void set_origin(const Position& origin) { origin_ = origin; }
    void set_target(const Position& target) { target_ = target; }

    // Makes the move invalid by resetting its positions and changing the move type
    void makeInvalid();

    // Converts the move to a string
    std::string to_string() const; 

private: 
    // Position from which the move is performed
    Position origin_;
    // Position on which the move is performed
    Position target_;
    // Type of move
    MoveType move_;
}; 

/*
Move class: represents a move performed by any player.
*/

#endif
