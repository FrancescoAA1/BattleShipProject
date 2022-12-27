#include "../include/Move.h"

Move::Move(const Position& origin, const Position& target, MoveType move)
{
    origin_ = origin;
    target_ = target;
    move_ = move;
}