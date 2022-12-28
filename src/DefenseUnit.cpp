#include "../include/DefenseUnit.h"

DefenseUnit::DefenseUnit()
{
    //imposto a vouoto lo stato della cella
    status_ = DefenseStatus::empty; 
    center_block_position_ = Position(); 
    //imposto a assolutamente invalida la posizioen del centro
    center_block_position_.make_absolute_invalid();
    //metto a zero la dimensione del blocco di appartenenza
    full_block_dimension_ = 0;  
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

void DefenseUnit::set_full_block_dimension(int full_block_dimension)
{
    full_block_dimension_ = full_block_dimension; 
}

void DefenseUnit::clear()
{
    //libero una cella mettendone lo stato a vuoto e il blocco in posizione invalida in assoluto
    status_ = DefenseStatus::empty; 
    center_block_position_.make_absolute_invalid(); 
    full_block_dimension_ = 0; 
}

void DefenseUnit::set_block_center(const Position& position)
{
    center_block_position_.set_x(position.X()); 
    center_block_position_.set_y(position.Y()); 
}
//due unità sono unguali se hanno lo stesso stato e posizione del centro di riferimento
bool operator==(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return (unit1.status() == unit2.status() && unit1.block_center() == unit2.block_center() && unit1.full_block_dimension() == unit2.full_block_dimension()); 
}

bool operator!=(const DefenseUnit& unit1, const DefenseUnit& unit2)
{
    return !(unit1 == unit2); 
}