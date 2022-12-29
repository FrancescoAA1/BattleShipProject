#include "../include/Move.h"

Move::Move(const Position& origin, const Position& target, MoveType move)
{
    origin_ = origin;
    target_ = target;
    move_ = move;
}

Move::Move()
{
    origin_ = Position();
    target_ = Position();

    makeInvalid();
}

void Move::makeInvalid()
{ 
    move_ = MoveType::invalid; 
    origin_.make_absolute_invalid(); 
    target_.make_absolute_invalid();
}