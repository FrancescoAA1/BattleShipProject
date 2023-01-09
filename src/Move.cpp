#include "../include/Move.h"
#include "../include/Utility.h"

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

std::string Move::to_string() const
{
    if(move_ == MoveType::showMap)
        return "AA AA"; 
    else if(move_ == MoveType::clearMap)
        return "YY YY"; 
    else return convert_to_command(origin_) + " " + convert_to_command(target_); 

}