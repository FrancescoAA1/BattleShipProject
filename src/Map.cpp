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

    // scrivo nella matrice
    // copio le posizioni poichè il metodo essendo non const come parametri potrebbe
    // modificharle nell'esecuzione
    Position stern = stern_position; 
    Position bow  = bow_position; 
    if(place_ship( stern, bow, center_position, orientation))
    {    
        // a questo punto posso aggiungere la nave al dizionario 
        ship_dictionary[center_position] = ship; 
    }
    else return false; 

    return true; 
}

// scrivo nella matrice una nave 
// torna true se l'operazione è correttamente eseguibile
bool Map::place_ship(Position& init, Position& end, const Position& center_block, Direction direction)
{
    // a parire dalla poppa (se è più piccola le inverto), nella direzione specificata, setto le unità 
    // della mappa di difesa a pieno fino alla prua
    if(direction == Direction::horizontal)
    {
        if(check_area_for_placing(center_block, std::abs(init.X() - end.X()), direction))
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
        else return false; 

    } 
    else if(direction == Direction::vertical)
    {
        if(check_area_for_placing(center_block, std::abs(init.Y() - end.Y()), direction))
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
        else return false; 
    }
    return true; 
}

// Funzioni per la DIFESA: 

// ritorna se una determinata posizione è libera nella mappa di difesa
bool Map::is_free_defense_position(const Position& target_destination) const
{
    return check_position(target_destination) && (defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::empty); 
}

// verifico se la coordinata di centro specificata può essere una posizione plausibile per una nave di lunghezza 
// length specificata e orientamento orientation.
// ritorna true se la nave ricoprirebbe una regione non vuota o non rientra nella matrice
bool Map::check_area_for_placing(const Position& target_destination, int length, Direction orientation) const
{
    // Controllo se nella direzione specificata spostandomi di length/2 ci sono celle piene 
    // controllo sia "Davanti" che "Indietro" (in accordo al senso della direzione) contemporaneamente
    // ammesso che la posizione generata sia corretta
    Position front = target_destination; 
    Position back = target_destination; 

    if(orientation == Direction::vertical)
    {
        // creo una posizione che individua l'offset 
        Position offset(0, length / 2); 

        while (offset.Y() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = target_destination + offset; 
            back = target_destination - offset; 
            //se sono posizioni corrette e vuote
            if(check_position(front) && check_position(back)
            && defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty
            && defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty)
            {
                // proseguo per la prossima posizione lungo la direzione verticale
                offset.set_y(offset.Y()-1); 
            }
            else return false; //altriementi lo spostamento non può essere valido
        }
    }
    else if(orientation == Direction::horizontal)
    {
        // creo una posizione che individua l'offset 
        Position offset(length / 2, 0); 

        while (offset.X() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = target_destination + offset; 
            back = target_destination - offset; 
            //se sono posizioni corrette e vuote
            if(check_position(front) && check_position(back)
            && defense_map_[front.Y()][front.X()].status() == DefenseStatus::empty
            && defense_map_[back.Y()][back.X()].status() == DefenseStatus::empty)
            {
                // proseguo per la prossima posizione lungo la direzione verticale
                offset.set_x(offset.X()-1); 
            }
            else return false; //altrimenti lo spostamento non può essere valido 
        }
    }
    return true; 
}

// muove una nave dalla sua posizione attuale al target specificato 
// aggiorna automaticamente la posizione della nave nel dizionario se va a buon fine
// la posizione target origin deve rappresentare il centro della nave da spostare
// il secondo paramentro è il target destination
// Ritorna true se lo spostamento è andato a buon fine
bool Map::move_ship(const Position& target_origin, const Position& target_destination)
{
    // se la posizione finale non è valida ritorno
    if(!check_position(target_destination)) return false; 

    Ship* ship_in_origin = get_ship(target_origin); 

    // se la nave non c'è nell'origine specificata allora ritorno
    if(ship_in_origin == nullptr) return false;

    // la nave c'è: inizio i test di posizionamento
    // (1) recupero la nave per vedere le dimensioni e l'orientamento => già fatto alla prima operazione
    // (2) verifico se la seconda posizione è libera: 
    if(defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::empty)
    {
        // mi ricavo la prua e la poppa così provo a posizionare la nave
        // se va a buon fine me la ha già scritta altrimenti ritorno 
        Position init; 
        Position end; 
        if(ship_in_origin->orientation() == Direction::horizontal)
        {
            init = target_destination - Position(ship_in_origin->size()/2 ,target_destination.Y()); 
            end = target_destination + Position(ship_in_origin->size()/2 ,target_destination.Y());  
        }
        else 
        {
            init = target_destination - Position(target_destination.X(), ship_in_origin->size()/2); 
            end = target_destination + Position(target_destination.X(), ship_in_origin->size()/2);  
        }
        // (3) se riesce a posizionarmela allora canello la vecchi aa re a e aggiorno il dizionario
        if(place_ship(init, end, target_destination, ship_in_origin->orientation()))
        {
            // (4) pulisco tutte le celle della vecchia occupazione
            clear_area(target_origin, ship_in_origin->size(), ship_in_origin->orientation()); 
            //rimuovo
            ship_dictionary.extract(target_origin); 
            //riaggiungo con la nuova chiave 
            ship_dictionary[target_destination] = ship_in_origin; 

            return true; 
        }
        else return false; 
    }
    else return false; //qui la posizione di destinazione è occupata
}

// funzione che pulisce tutte le caselle nella regione specificata: centro, lunghezza e direzione
// le coordinate che andrà a pulire devono essere già testate come corrette!
void Map::clear_area(const Position& center_block, int length, Direction orientation)
{
    // Mi muovo se nella direzione specificata spostandomi di length/2 
    // vado sia "Davanti" che "Indietro" (in accordo al senso della direzione) contemporaneamente
    Position front; 
    Position back;

    //cancello il centro e poi il resto 
    defense_map_[center_block.Y()][center_block.X()].clear();  

    if(orientation == Direction::vertical)
    {
        // creo una posizione che individua l'offset 
        Position offset(length / 2, 0); 

        while (offset.Y() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = center_block + offset; 
            back = center_block - offset; 

            defense_map_[front.Y()][front.X()].clear(); 
            defense_map_[back.Y()][back.X()].clear(); 
            // proseguo per la prossima posizione lungo la direzione verticale
            offset.set_y(offset.Y()-1); 
        }
    }
    else if(orientation == Direction::horizontal)
    {
        // creo una posizione che individua l'offset 
        Position offset(length / 2, 0); 

        while (offset.X() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = center_block + offset; 
            back = center_block - offset; 

            defense_map_[front.Y()][front.X()].clear(); 
            defense_map_[back.Y()][back.X()].clear(); 
            // proseguo per la prossima posizione lungo la direzione verticale
            offset.set_x(offset.X()-1); 
        }
    }

}