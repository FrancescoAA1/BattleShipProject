#include "../include/DefenseMap.h"

// contruttore di default della classe 
// che inizializza tutte le matrici come vuote
DefenseMap::DefenseMap()
{
    //imposto a vuoto tutta la matrice di difesa
    clear_defense_map(); 
}

// FUnzioni UTILITARIE

// metodo che resetta tutta la matrice di difesa
void DefenseMap::clear_defense_map()
{
    // imposto tutte le celle 
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            defense_map_[i][j].clear(); 
        }
    }
}

// funzione che pulisce tutte le caselle nella regione specificata: centro, lunghezza e direzione
// le coordinate che andrà a pulire devono essere già testate come corrette!
void DefenseMap::clear_area(const Position& center_block, int length, Direction orientation)
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
        Position offset{0, length / 2}; 

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
        Position offset{length / 2, 0}; 

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

// scrivo nella matrice una nave 
// inizio e fine devono già condividere la stessa riga o la stessa colonna in accordo con la direzione
// torna true se l'operazione è correttamente eseguibile
bool DefenseMap::place_ship(Position& init, Position& end, const Position& center_block, int block_dimension ,Direction direction)
{
    // a parire dalla poppa (se è più piccola le inverto), nella direzione specificata, setto le unità 
    // della mappa di difesa a pieno fino alla prua
    if(direction == Direction::horizontal)
    {
        // controllo se l'area che dovrebbe ricoprire è libera e se la distanza tra prua e poppa coincide con 
        // la dimensione del blocco da scrivere 
        if(check_area_for_placing(center_block, std::abs(init.X() - end.X()), direction) && (std::abs(init.X() - end.X()) == block_dimension))
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
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);  
                init.set_x(init.X() + 1);  
            }
            //scrivo l'ultima 
            defense_map_[end.Y()][end.X()].set_block_center(center_block); 
            defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken);
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension); 
        }
        else return false; 

    } 
    else if(direction == Direction::vertical)
    {
        if(check_area_for_placing(center_block, std::abs(init.Y() - end.Y()), direction) && (std::abs(init.Y() - end.Y()) == block_dimension))
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
                defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
                init.set_y(init.Y() + 1);  
            }
            //scrivo l'ultima 
            defense_map_[end.Y()][end.X()].set_block_center(center_block); 
            defense_map_[end.Y()][end.X()].set_status(DefenseStatus::taken); 
            defense_map_[init.Y()][init.X()].set_full_block_dimension(block_dimension);
        }
        else return false; 
    }
    return true; 
}

// verifico se una posizione è valida: deve restare tra la larghezza e l'altezza delle matrici
bool DefenseMap::check_position(const Position& position) const
{
    return (position.X() >= 0 && position.X() < kWidth && position.Y() >= 0 && position.X() < kHeight); 
}

// verifico se la coordinata di centro specificata può essere una posizione plausibile per una nave di lunghezza 
// length specificata e orientamento orientation.
// ritorna true se la nave ricoprirebbe una regione non vuota o false altrimenti
bool DefenseMap::check_area_for_placing(const Position& target_destination, int length, Direction orientation) const
{
    // Controllo se nella direzione specificata spostandomi di length/2 ci sono celle piene 
    // controllo sia "Davanti" che "Indietro" (in accordo al senso della direzione) contemporaneamente
    // ammesso che la posizione generata sia corretta
    Position front = target_destination; 
    Position back = target_destination; 

    if(orientation == Direction::vertical)
    {
        // creo una posizione che individua l'offset 
        Position offset{0, length / 2}; 

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
        Position offset{length / 2, 0}; 

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

// Funzioni per la DIFESA: 

// ritorna se una determinata posizione è libera nella mappa di difesa
bool DefenseMap::is_free_defense_position(const Position& target_destination) const
{
    return check_position(target_destination) && (defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::empty); 
}

// muove una nave dalla sua posizione attuale al target specificato 
// la posizione target origin deve rappresentare il centro della nave da spostare
// il secondo paramentro è il target destination
// Ritorna true se lo spostamento è andato a buon fine
bool DefenseMap::move_ship(const Position& target_origin, const Position& target_destination)
{
    // se la posizione finale o iniziale non è valida ritorno
    if(!check_position(target_destination) || !check_position(target_origin)) return false; 

    // se la nave non c'è nell'origine specificata o la destinazione non è vuota allora ritorno 
    if(defense_map_[target_origin.Y()][target_origin.X()].status() != DefenseStatus::empty ||
    defense_map_[target_destination.Y()][target_destination.X()].status() != DefenseStatus::empty) return false;

    // Ora posizioni di origine e destinazione sono valide => inizio i test di spostamento
    // (1) dal blocco di origine (centro della nave) mi ricavo la grandezza del blocco totale
    int dimension = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension(); 
    // (2) determino la direzione guardantomi a lato: 
    // a) se a destra o sinistra non ho nulla allora 
    // b) guardo in alto e in basso 
    // se non ho nulla => è un sottomarino
    // se trovo a dx e sx => è una nave in orizzontale 
    // altrimeni è in vericale
    Position offset_o{1,0}; 
    Position offset_v{0,1}; 

    // di deafult pongo a vericale 
    Direction direction = Direction::vertical; 

    // siccome ho il centro basta vedere a destra => se c'è qualcosa c'è sicuramente anche a sinistra a 
    // meno che non sia un sottomarino
    // se la posizione a destra non è valida => è sul bordo destro ed è sicuramente in vericale (a meno di un sottomarino)
    // se il test sotto fallisce => sicuramente la nave è in verticale o è un sottomarino. 
    // Test a DESTRA
    if(check_position(target_origin + offset_o))
    {
        if(defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty)
            direction = Direction::horizontal; 
    }
    // provo ora a scriverla nella nuova area 
    // se va a buon fine è già nella posizione corretta e cancello la vecchia are a occupata
    // altrimenti ritorno. 
    // Al sottomarino passo la direzione di default => essendo di un blocco è indifferente 

    // prima però recupero prua e poppa nella nuova destinazione 
    Position bow; 
    Position stern; 

    // Sommo e sottraggo alla x o alla y della destinazione metà della lunghezza del blocco
    if(direction == Direction::horizontal)
    {
        bow = target_destination + Position{dimension/2,0}; 
        stern = target_destination - Position{dimension/2,0};  
    }
    else
    {
        bow = target_destination + Position{0, dimension/2}; 
        stern = target_destination - Position{0, dimension/2};      
    }

    // si occupa palce ship di verificare che l'area sia libera 
    if(place_ship(bow, stern, target_destination, dimension, direction))
    {
        // lo spostamento è andato a buon fine e la nave è stata scritta nella posizione corretta
        // allora la cancello dalla vecchia
        clear_area(target_origin, dimension, direction); 
        return true; 
    }
    else return false; 
}
    // sparo ad una nave della mia collezione poichè è stata colpita
    // ritorno un blocco di attacco per rappresentare lo stato finale dell'operazione da comunicare 
    // all'esterno.
    // Se la nave è stata affondata richiamare il metodo remove ship se si desidera rimuovere dalla mappa 
    AttackUnit DefenseMap::receive_shot(const Position& target_destination)
    {
        //controllo se la posizione è valida e se lo è verifico se continene una posizione occupata e non colpita
        if(check_position(target_destination) && defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::taken)
        {
            defense_map_[target_destination.Y()][target_destination.X()].set_status(DefenseStatus::hit); 
            return AttackUnit::full_and_hit; 
        }
        else return AttackUnit::empty_and_hit; 
    }