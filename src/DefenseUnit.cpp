#include "../include/DefenseUnit.h"

DefenseUnit::DefenseUnit()
{
    //imposto a vouoto lo stato della cella
    status_ = DefenseStatus::empty; 
    center_block_position_ = Position(); 
    //imposto a assolutamente invalida la posizioen del centro
    center_block_position_.make_absolute_invalid(); 
}

DefenseUnit::DefenseUnit(DefenseStatus status, const Position& center_block_position)
{
    status_ = status; 
    center_block_position_ = center_block_position; 
}

void DefenseUnit::set_status(DefenseStatus status)
{ 
    status_ = status; 
}

void DefenseUnit::clear()
{
    //libero una cella mettendone lo stato a vuoto e il blocco in posizione invalida in assoluto
    status_ = DefenseStatus::empty; 
    center_block_position_.make_absolute_invalid(); 
}

void DefenseUnit::set_center_block(const Position& position)
{
    center_block_position_.set_x(position.X()); 
    center_block_position_.set_y(position.Y()); 
}
//due unità sono unguali se hanno lo stesso stato e posizione del centro di riferimento
bool operator==(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return (unit1.status() == unit2.status() && unit1.block_center() == unit2.block_center()); 
}

bool operator!=(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return !(unit1 == unit2); 
}