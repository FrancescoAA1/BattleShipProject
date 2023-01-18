// Author: Mattia Galassi
#include "../include/AttackGrid.h"

// costruttore di default che setta tutto a vuoto
AttackGrid::AttackGrid()
{
    clear_area();
}

// funzione che permette di impostare come spotted (scoperta) la posizione selezionata
// aggiornando la mappa d'attacco
// ritorna true se lo spot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackGrid::spot_position(const Position &target_destination)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if (check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = AttackUnit::spotted;
        return true;
    }
    else
        return false;
}

// imposta a hit la cella della mappa d'attacco di target specificato
// aggiornando la mappa d'attacco
// ritorna true se lo shot è andato a buon fine
// lo spot fallisce se la cella non è vuota o non è valida
bool AttackGrid::shot_position(const Position &target_destination, AttackUnit shot_status)
{
    // Se la posizione è valida aggirno la mappa di attacco come da aspettativa
    if (check_position(target_destination))
    {
        attack_grid_[target_destination.Y()][target_destination.X()] = shot_status;
        return true;
    }
    else
        return false;
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
bool AttackGrid::check_position(const Position &position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.Y() < kHeight);
}

// funzione che scrive in una stringa la mappa
std::string AttackGrid::to_string() const
{
    std::string result = ">  ";
    // leggo tutte le celle e le scrivo nella sringa risultante
    // il loro corrispondente valore per la rappresentazione
    // aggiungendo la colonna laterale di lettere
    // e la riga finale di numeri per le coordinates
    char row_index = kFirstRowLetter;
    int column_index = kFirstColumnNumber;

    for (int i = 0; i < kWidth; i++)
    {
        result += std::to_string(column_index);
        result += " ";
        if (i < 9)
        {
            result += " ";
        }
        column_index++;
    }
    result += "\n";

    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            // Scrivo la riga indice:
            if (j == 0)
            {
                if (row_index >= 'J')
                {
                    row_index = row_index + 2;
                    result.append(1, row_index);
                    row_index = row_index - 2;
                }
                else
                {
                    result.append(1, row_index);
                }
                result += "  ";

                row_index++;
            }
            switch (attack_grid_[i][j])
            {
            case AttackUnit::unknown:
                result += "   ";
                break;
            case AttackUnit::empty_and_hit:
                result += kHitAndEmptySymbol;
                result += "  ";
                break;
            case AttackUnit::full_and_hit:
                result += kHitAndFullSymbol;
                result += "  ";
                break;
            case AttackUnit::spotted:
                result += kSpottedSymbol;
                result += "  ";
                break;
            }
        }
        result += "\n";
    }

    return result;
}

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream &operator<<(std::ostream &data_stream, const AttackGrid &attack_grid)
{
    return data_stream << attack_grid.to_string();
}

// funzione che pulisce dalla matrice tutte le caselle impostate ad X
void AttackGrid::clear_all_full_and_hit()
{
    // imposto tutte le celle con carettere X a empty
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::full_and_hit)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}

// funzione che pulisce dalla matrice tutte le caselle impostate ad O
void AttackGrid::clear_all_full_and_empty()
{
    // imposto tutte le celle con carettere O a empty
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::empty_and_hit)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}

// funzione che pulisce dalla matrice tutte le caselle impostate ad Y
void AttackGrid::clear_sonared()
{
    // imposto tutte le celle con carettere O a empty
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if (attack_grid_[i][j] == AttackUnit::spotted)
            {
                attack_grid_[i][j] = AttackUnit::unknown;
            }
        }
    }
}