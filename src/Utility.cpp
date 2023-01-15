#include "../include/Utility.h"
#include <iostream>

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::string visual_merge_grid(const AttackGrid &attack_grid, const DefenseMap &defense_map)
{
    // ottengo tutte le linee di cui sono composte le mappe splittandole sul carattere "a capo"
    std::vector<std::string> line_d_map = splitstr(defense_map.to_string(), "\n");
    std::vector<std::string> line_a_grid = splitstr(attack_grid.to_string(), "\n");

    // ora faccio un merge linea per linea delle due
    std::string result = "";
    int i = 0;
    int j = 0;

    while (i < line_d_map.size() && j < line_a_grid.size())
    {
        result += line_d_map[i];
        result += "        ";
        result += line_a_grid[j];
        result += "\n";
        i++;
        j++;
    }
    return result;
}

// funzione per fare split di strighe su un determinato carattere
std::vector<std::string> splitstr(std::string str, std::string delim)
{
    std::vector<std::string> out{};
    int start = 0;
    // ricerco la posizione del primo delimitatore se presente
    int end = str.find(delim);

    while (end != -1)
    {
        // ho trovato un delimitatore
        // aggiungo la sottostringa al vettore fino a quel punto e procedo alla prossima ricerca
        out.push_back(str.substr(start, end - start));
        start = end + delim.size();
        end = str.find(delim, start);
    }
    // aggiungo l'ultimo
    out.push_back(str.substr(start, end - start));

    return out;
}

int get_random(int range)
{
    static int counter = 0;
    int temp = 0;

    if (counter % 2 == 0)
    {
        std::srand(time(NULL));
        temp = (std::rand() + counter) % range;
    }

    else
    {
        std::srand(1);
        temp = (std::rand() + counter) % range;
    }

    counter++;
    return temp;
}

Position convert_to_position(const std::string &coordinate)
{
    Position pos{};

    try
    {
        // sottrazione del valore ASCII di 'A' al primo carattere della stringa
        // conversione da char ad int
        int x;
        // se le colonne sono J o K allora non va bene e ritorno invalida
        if (coordinate[0] == 'J' || coordinate[0] == 'K')
        {
            pos.make_absolute_invalid();
            return pos;
        }
        if (coordinate[0] > 'J') // elimino le colonne j e k
            x = coordinate[0] - kDefaultCapitalAscii - 2;
        else
            x = coordinate[0] - kDefaultCapitalAscii;

        // conversione da stringa ad intero dell'ultima parte della coppia di coordinate (numero)
        // stoi lancia std::invalid_argument exception se la sottostringa non è un numero
        std::string y_pos = coordinate.substr(1, coordinate.size() - 1);
        int y = std::stoi(y_pos) - 1;

        //controllo che le cifre del numero siano uguali in numero alla lunghezza della
        //sottostringa precedentemente prelevata
        if (count_digits(y) != y_pos.size())
        {
            pos.make_absolute_invalid();
            return pos;
        }

        // controllo che x e y siano nel range delle dimensioni delle due mappe
        // NOTA: sarebbe opportuno poter accedere alle costanti di dimensione della mappa
        if (x >= 0 && x <= DefenseMap::kWidth && y >= 0 && y <= DefenseMap::kHeight)
        {
            pos = Position(x, y);
            return pos;
        }
        else
        {
            // se una delle due cooridnate non è valida, viene ritornata posizione non valida
            pos.make_absolute_invalid();
            return pos;
        }
    }
    catch (std::invalid_argument)
    {
        pos.make_absolute_invalid();
        return pos;
    }
}

std::string convert_to_command(const Position &position)
{
    if (position.X() >= 0 && position.X() <= 11 && position.Y() >= 0 && position.Y() <= 11)
    {

        // conversione esplicita da int ad a char (sicura) della coordinata X della posizione
        // stringa formata dal carattere a cui viene sommato il valore ASCII di "A"
        std::string letter(1, (char)position.X() + kDefaultCapitalAscii);
        if (letter[0] >= 'J')
            letter[0] = letter[0] + 2;

        // conversione da int a string della coordinata Y della posizione
        std::string number = std::to_string(position.Y() + 1);

        // concatenazione delle due stringhe contenenti le coordinate in formato (A1)
        std::string coordinate = letter + number;
        return coordinate;
    }
    else
        return "";
}

int count_digits(int n)
{
    if (n / 10 == 0)
        return 1;
    return 1 + count_digits(n / 10);
}
