#include "../include/Position.h"

Position::Position()
{
    x_ = 0; 
    y_= 0; 
}

//inizializzo con i valori passati 
Position::Position(int x, int y)
{
    x_ = x; 
    y_ = y; 
}


void Position::set_x(int value)
{
    x_= value;
}

void Position::set_y(int value)
{
    y_= value;
}

void Position::make_absolute_invalid()
{
    x_ = INVALID_X_POSITION; 
    y_ = INVALID_Y_POSITION;
}

bool Position::is_absolute_invalid()
{
    return x_ == INVALID_X_POSITION && y_ == INVALID_Y_POSITION; 
}

Position operator+(const Position& p1, const Position& p2)
{
    return Position(p1.X() + p2.X(), p1.Y() + p2.Y()); 
}
Position operator-(const Position& p1, const Position& p2)
{
    return Position(p1.X() - p2.X(), p1.Y() - p2.Y()); 
}
bool operator==(const Position& p1, const Position& p2)
{
    return (p1.X() == p2.X() && p1.Y() == p2.Y()); 
}
bool operator!=(const Position& p1, const Position& p2)
{
    return !(p1 == p2); 
}

Position operator/(const Position& p, int coeff)
{
    return Position(p.X()/coeff, p.Y()/coeff); 
}

Position operator*(const Position& p, int coeff)
{
    return Position(p.X()*coeff, p.Y()*coeff); 
}