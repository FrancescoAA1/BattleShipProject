#include "../include/AttackGrid.h"
#include <ostream>
#include <iostream>

// costruttore di default che setta tutto a vuoto
AttackGrid::AttackGrid()
{
    clear_area(); 
}

// funzione che permette di impostare come spotted (scoperta) la posizione selezionata
// aggiornando la mappa d'attacco
// ritorna true se lo spot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackGrid::spot_position(const Position& target_destination)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if(check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = AttackUnit::spotted; 
        return true; 
    }
    else return false; 
}

// imposta a hit la cella della mappa d'attacco di target specificato
// aggiornando la mappa d'attacco
// ritorna true se lo shot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackGrid::shot_position(const Position& target_destination, AttackUnit shot_status)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if(check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = shot_status; 
        return true; 
    }
    else return false; 
}

// funzione che pulisce tutte le caselle nella matrice 
void AttackGrid::clear_area()
{
    // imposto tutte le celle 
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            attack_grid_[i][j] = AttackUnit::unknown; 
        }
    }
}

// verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
bool AttackGrid::check_position(const Position& position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.X() < kHeight); 
}

// funzione che scrive in una stringa la mappa 
std::string AttackGrid::to_string() const
{
    std::string result = "X "; 
    // leggo tutte le celle e scrivo nell'out stream 
    // il loro corrispondente valore per la rappresentazione
    // aggiungendo la colonna laterale di lettere
    // e la riga finale di numeri per le coordinates
    char row_index = kFirstRowLetter; 
    int column_index = kFirstColumnNumber;

    for (int i = 0; i < kHeight; i++)
    {
        result.append(1, row_index);
        result += " ";
        row_index++;
    }

    result += "\n";

    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            //Scrivo la colonna indice: 
            if(j == 0)
            {
                result += std::to_string(column_index); 
                column_index++;
                if(i<9)
                {
                    result += " ";
                }
            }
            switch (attack_grid_[i][j])
            {
                case AttackUnit::unknown:
                    result+=" ";
                break;
                case AttackUnit::empty_and_hit:
                    result+=kHitAndEmptySymbol;
                break;
                case AttackUnit::full_and_hit:
                    result+=kHitAndFullSymbol;
                break;  
                case AttackUnit::spotted:
                    result+=kSpottedSymbol;
                break; 
            } 
        }
        result+="\n"; 
    }
    
    return result; 
}

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream& operator<<(std::ostream& data_stream,  const AttackGrid& attack_grid)
{
    return data_stream<<attack_grid; 
}