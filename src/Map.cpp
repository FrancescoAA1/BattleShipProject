#include "../include/Map.h"

// costruttore di default
Map::Map()
{
    // avendo definito costruttori di default per la classe DefenseUnit
    // sono già impostate tutte a vuoto le unità della matrice di difesa

    //metto a vuoto tutte le unità della matrice d'attacco
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            attack_map_[i][j] = AttackUnit::empty; 
        }
        
    }
    
    // creo il dizionario con il numero di navi iniziale => 8
    ship_dictionary = std::unordered_map<Position,Ship*>(kInitiatlShipNumber); 
}

// Funzioni UTILITARIE: 

// verifico se una posizione è valida: deve restare tra la larghezza e l'altezza delle matrici
bool Map::check_position(const Position& position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.X() < kHeight); 
}

// ritorno la nave presente nella posizione (centro della nave)
// specificata. Se non c'è torno nullptr
Ship* Map::get_ship(const Position& center_position)
{
    // se l'iteratore ritorneto è end() => non è presente
    if(ship_dictionary.find(center_position) == ship_dictionary.end())
        return nullptr; 
    else return ship_dictionary[center_position]; //altrimenti ritorno il puntatore alla nave corretta
}

// aggiugno una nave al dizionario e controllo se i parametri passati sono ammissibili
bool Map::add_ship(const Position& bow_position, const Position& stern_position,Ship* ship)
{
    // se sia x che y sono diverse allora non è ne in orizzontale ne il vericale = > non valida
    if(bow_position.X() != stern_position.X() && bow_position.Y() != stern_position.Y())
        return false; 
    
    Position center_position; 
    Direction orientation; 

    // controllo se è in verticale => hanno la stessa x
    if(bow_position.X() == stern_position.X())
    {
        // se l'orientamento della nave è orizzontale => errore
        if(ship->orientation() == Direction::horizontal)
            return false; 

        // controllo se la lunghezza è diversa dalla differenza delle y
        if(ship->size() != (std::abs(bow_position.Y() - stern_position.Y())))
            return false; 
        
        // qui la nave è correttemnete inseribile nel dizionario
        // calcolo il centro e la aggiungo => (a+b)/2
        int y_center = (bow_position.Y() + stern_position.Y())/2; 
        center_position = Position(y_center, bow_position.X()); 

        // ultimo controllo è che non ci sia già una nave in quella posizione 
        if(get_ship(center_position) != nullptr)
            return false;

        orientation = Direction::vertical; 
    }

    // controllo se è in orizzontale => hanno la stessa y
    if(bow_position.Y() == stern_position.Y())
    {
        // se l'orientamento della nave è vericale => errore
        if(ship->orientation() == Direction::vertical)
            return false; 

        // controllo se la lunghezza è diversa dalla differenza delle x
        if(ship->size() != (std::abs(bow_position.X() - stern_position.X())))
            return false; 
        
        // qui la nave è correttemnete inseribile nel dizionario
        // calcolo il centro e la aggiungo => (a+b)/2
        int x_center = (bow_position.X() + stern_position.X())/2; 
        center_position = Position(x_center, bow_position.X()); 

        // ultimo controllo è che non ci sia già una nave in quella posizione 
        if(get_ship(center_position) != nullptr)
            return false;
            
        orientation = Direction::horizontal; 
    }

    // a questo punto posso aggiungere la nave al dizionario e scriverla sulla matrice
    ship_dictionary[center_position] = ship; 
    // scrivo nella matrice
    // copio le posizioni poichè il metodo essendo non const come parametri potrebbe
    // modificharle nell'esecuzione
    Position stern = stern_position; 
    Position bow  = bow_position; 
    place_ship( stern, bow, center_position, orientation); 

    return true; 
}

// scrivo nella matrice una nave
void Map::place_ship(Position& init, Position& end, Position& center_block, Direction direction)
{
    // a parire dalla poppa (se è più piccola le inverto), nella direzione specificata, setto le unità 
    // della mappa di difesa a pieno fino alla prua
    if(direction == Direction::horizontal)
    {
        if(init.X() > end.X())
        {
            int tmp = end.X(); 
            end.set_x(init.X()); 
            init.set_x(tmp); 
        }

        while(init != end)
        {
            defense_map_[init.Y()][init.X()].set_block_center(center_block); 
            defense_map_[init.Y()][init.X()].set_status(DefenseStatus::taken); 
            init.set_x(init.X() + 1);  
        }
        //scrivo l'ultima 
        defense_map_[end.Y()][end.X()].set_block_center(center_block); 
        defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken); 
    } 
    else if(direction == Direction::vertical)
    {
        if(init.Y() > end.Y())
        {
            int tmp = end.Y(); 
            end.set_y(init.Y()); 
            init.set_y(tmp); 
        }

        while(init != end)
        {
            defense_map_[init.Y()][init.X()].set_block_center(center_block); 
            defense_map_[init.Y()][init.X()].set_status(DefenseStatus::taken); 
            init.set_y(init.Y() + 1);  
        }
        //scrivo l'ultima 
        defense_map_[end.Y()][end.X()].set_block_center(center_block); 
        defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken); 
    }
}

// Funzioni per la DIFESA: 

// ritorna se una determinata posizione è libera nella mappa di difesa
bool Map::is_free_defense_position(const Position& target_destination) const
{
    return check_position(target_destination) && (defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::empty); 
}