#include "../include/AttackMap.h"
#include <ostream>

// costruttore di default che setta tutto a vuoto
AttackMap::AttackMap()
{
    clear_area(); 
}

// funzione che permette di impostare come spotted (scoperta) la posizione selezionata
// aggiornando la mappa d'attacco
// ritorna true se lo spot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackMap::spot_position(const Position& target_destination)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if(check_position(target_destination))
    {
        attack_map_[target_destination.Y()][target_destination.X()] = AttackUnit::spotted; 
        return true; 
    }
    else return false; 
}

// imposta a hit la cella della mappa d'attacco di target specificato
// aggiornando la mappa d'attacco
// ritorna true se lo shot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackMap::shot_position(const Position& target_destination, AttackUnit shot_status)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if(check_position(target_destination))
    {
        attack_map_[target_destination.Y()][target_destination.X()] = shot_status; 
        return true; 
    }
    else return false; 
}

// funzione che pulisce tutte le caselle nella matrice 
void AttackMap::clear_area()
{
    // imposto tutte le celle 
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            attack_map_[i][j] = AttackUnit::unknown; 
        }
    }
}

// verifica se una determinata posizione è valida o meno (deve rientrare nelle dimensioni della mtrice)
bool AttackMap::check_position(const Position& position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.X() < kHeight); 
}
// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream& AttackMap::operator<<(std::ostream& data_stream)
{
    // leggo tutte le celle e scrivo nell'out stream 
    // il loro corrispondente valore per la rappresentazione
    // aggiungendo la colonna laterale di lettere
    // e la riga finale di numeri per le coordinates
    char row_index = kFirstRowLetter; 
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            data_stream<<row_index; 
            row_index++; 
            //Scrivo la colonna indice: 
            if(i == 8)
            {
                row_index+=2; 
            }
            switch (attack_map_[i][j])
            {
                case AttackUnit::unknown:
                    data_stream<<" ";
                break;
                case AttackUnit::empty_and_hit:
                    data_stream<<kHitAndEmptySymbol;
                break;
                case AttackUnit::full_and_hit:
                    data_stream<<kHitAndFullSymbol;
                break;  
                case AttackUnit::spotted:
                    data_stream<<kSpottedSymbol;
                break; 
            } 
        }
        data_stream<<"\n"; 
    }
    // scrivo l'ultima riga indice
    data_stream<<" "; 
    int column_index = kFirstColumnNumber;
    for (int i = 0; i < kWidth; i++)
    {
        data_stream<<column_index; 
        column_index++; 
    }
    
    return data_stream; 
}