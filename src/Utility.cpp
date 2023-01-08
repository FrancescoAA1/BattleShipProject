#include "../include/Utility.h"

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
        result+= line_d_map[i]; 
        result+="        "; 
        result+=line_a_grid[j]; 
        result+="\n"; 
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

// funzione che permette di convertire una posizione in una stringa che la rappresneta per al mappa
std::string convert_to_visual_position(const Position& position)
{
    // sommo 1 alla colonna e converto in lettera l'ascissa
    std::string result = ""; 

    char column = kDefaultCapitalAscii + position.Y(); 

    if(column == 'J')
        column = 'M'; 
    if(column == 'K')
        column = 'N'; 

    result.append(1, column); 

    result+= position.X() + 1; 

    return result; 
}


int get_random(int range)
{
    static int counter = 0;
    int temp = 0;
    
    if(counter % 2 == 0)
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