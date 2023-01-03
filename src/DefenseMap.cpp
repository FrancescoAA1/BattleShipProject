#include "../include/DefenseMap.h"
#include <algorithm>

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
    if(defense_map_[target_origin.Y()][target_origin.X()].status() == DefenseStatus::empty ||
    defense_map_[target_destination.Y()][target_destination.X()].status() != DefenseStatus::empty ||
    defense_map_[target_origin.Y()][target_origin.X()].block_center() != target_origin) return false;

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

    // di deafult pongo a vericale 
    Direction direction = Direction::vertical; 

    // siccome ho il centro basta vedere a destra se la posizione non è vuota e ha lo stesso valore del centro del 
    // blocco di riferimento=> se c'è qualcosa c'è sicuramente anche a sinistra a 
    // meno che non sia un sottomarino
    // se la posizione a destra non è valida => è sul bordo destro ed è sicuramente in vericale (a meno di un sottomarino)
    // se il test sotto fallisce => sicuramente la nave è in verticale o è un sottomarino. 
    // Test a DESTRA
    if(check_position(target_origin + offset_o)) 
    {
        if(defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty
        && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin )
            direction = Direction::horizontal; 
    }

    // verifico che l'area di destinazione non sia accerchiata: la nave deve aver modo di poterci entrare
    if(is_sorrounded(target_destination, dimension, direction)) return false; 
    
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
// ritorno una poccia (posizione del centro della nave colpita, stato dell'attacco)
// se il tiro non è andato a segno allora ritorna O e la posizione del centro invalida
// Se la nave è stata affondata richiamare il metodo remove ship se si desidera rimuovere dalla mappa 
std::pair<Position, AttackUnit> DefenseMap::receive_shot(const Position& target_destination)
{
    Position center_block{}; 
    //controllo se la posizione è valida e se lo è verifico se continene una posizione occupata e non colpita
    if(check_position(target_destination) && defense_map_[target_destination.Y()][target_destination.X()].status() == DefenseStatus::taken)
    {
        defense_map_[target_destination.Y()][target_destination.X()].set_status(DefenseStatus::hit); 
        center_block = defense_map_[target_destination.Y()][target_destination.X()].block_center();  

        return { center_block, AttackUnit::full_and_hit }; 
    }
    else return { center_block, AttackUnit::empty_and_hit };  
}

// funzione che permette di rimuovere una nave dalla mappa 
bool DefenseMap::remove_ship(const Position& target_origin)
{
    // verifico se la posizione è corretta e se c'è una nave che abbia il valore del centro uguale al target_origin
    if(check_position(target_origin) && defense_map_[target_origin.Y()][target_origin.X()].block_center() == target_origin)
    {
        int length = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension();  

        // determino la direzione: 
        Position offset_o{1,0}; 

        // di deafult pongo a vericale 
        Direction direction = Direction::vertical; 

        // siccome ho il centro basta vedere a destra se la posizione non è vuota e ha lo stesso valore del centro del 
        // blocco di riferimento=> se c'è qualcosa c'è sicuramente anche a sinistra a 
        // meno che non sia un sottomarino
        // se la posizione a destra non è valida => è sul bordo destro ed è sicuramente in vericale (a meno di un sottomarino)
        // se il test sotto fallisce => sicuramente la nave è in verticale o è un sottomarino. 
        // Test a DESTRA
        if(check_position(target_origin + offset_o)) 
        {
            if(defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty
            && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin )
                direction = Direction::horizontal; 
        }
        //pulisco l'area 
        clear_area(target_origin, length, direction); 
        return true; 

    } else return false; 
}

// funzione che permette di ottenere i centri delle navi nell'area specificata di lato side centrata nel punto
// target_origin specificato
// se l'area fuoriesce dalla matrice ne fa l'intersezione. Se l'area è più vasta della matrice e 
// la contiene => ritorna tutti i centri della matrice
std::vector<Position> DefenseMap::discovers_neighbors(const Position& target_origin, int side) const 
{
    std::vector<Position> neighbors_position{}; 
    // se la posizione non è corretta ritorno un vettore vuoto 
    if(!check_position(target_origin)) return neighbors_position; 
    // determino il vertice di partenza 
    Position start = target_origin - Position{side/2, side/2}; 
    Position tmp; 
    // cerco per tutta l'area posizioni non vuote e aggiugno il loro centro 
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if(check_position(start))
            {
                if(defense_map_[start.Y()][start.X()].status() != DefenseStatus::empty)
                {
                    // controllo se non è già presente 
                    tmp = defense_map_[start.Y()][start.X()].block_center(); 
                    if(std::find(neighbors_position.begin(), neighbors_position.end(), tmp) == neighbors_position.end())
                        neighbors_position.push_back(tmp);
                }
            }
            start.set_x(start.X() + j); 
        }
        start.set_y(start.Y() + i); 
        start.set_x(target_origin.X() - side/2); 
    }
    return neighbors_position; 
}

// funzione che cura la nave con centro specificato in target_origin
bool DefenseMap::fix_ship(const Position& target_origin)
{
    // verifico se la posizione è corretta e se c'è una nave che abbia il valore del centro uguale al target_origin
    if(!check_position(target_origin) || defense_map_[target_origin.Y()][target_origin.X()].block_center() != target_origin)
        return false; 

   // determino la direzione: 
    Position offset_o{1,0}; 

    // di deafult pongo a vericale 
    Direction orientation = Direction::vertical; 

    // siccome ho il centro basta vedere a destra se la posizione non è vuota e ha lo stesso valore del centro del 
    // blocco di riferimento=> se c'è qualcosa c'è sicuramente anche a sinistra a 
    // meno che non sia un sottomarino
    // se la posizione a destra non è valida => è sul bordo destro ed è sicuramente in vericale (a meno di un sottomarino)
    // se il test sotto fallisce => sicuramente la nave è in verticale o è un sottomarino. 
    // Test a DESTRA
    if(check_position(target_origin + offset_o)) 
    {
        if(defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].status() != DefenseStatus::empty
        && defense_map_[(target_origin + offset_o).Y()][(target_origin + offset_o).X()].block_center() == target_origin )
            orientation = Direction::horizontal; 
    } 
    // passo al ripristino delle celle della nave 
    int size = defense_map_[target_origin.Y()][target_origin.X()].full_block_dimension(); 

    
    defense_map_[target_origin.Y()][target_origin.X()].set_status(DefenseStatus::taken);  
    Position front; 
    Position back; 

    if(orientation == Direction::vertical)
    {
        // creo una posizione che individua l'offset 
        Position offset{0, size / 2}; 

        while (offset.Y() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = target_origin + offset; 
            back = target_origin - offset; 

            defense_map_[front.Y()][front.X()].set_status(DefenseStatus::taken); 
            defense_map_[back.Y()][back.X()].set_status(DefenseStatus::taken); 
            // proseguo per la prossima posizione lungo la direzione verticale
            offset.set_y(offset.Y()-1); 
        }
    }
    else if(orientation == Direction::horizontal)
    {
        // creo una posizione che individua l'offset 
        Position offset{size / 2, 0}; 

        while (offset.X() != 0)
        {
            // mi preparo ad andare avanti e indietro sommando l'offset
            front = target_origin + offset; 
            back = target_origin - offset; 

            defense_map_[front.Y()][front.X()].set_status(DefenseStatus::taken); 
            defense_map_[back.Y()][back.X()].set_status(DefenseStatus::taken); 
            // proseguo per la prossima posizione lungo la direzione verticale
            offset.set_x(offset.X()-1); 
        }
    } 
    return true; 
}

// funzione che scopre tutte le navi in un'area dimxdim a partire del centro specificato come target
// ritona un'area che rappresenta una matrice dimxdim scritta per righe
// l'intero serve a specificare il lato di dimensione per l'area
// se l'area non rientra nella matrice ne fa l'intersezione 
// se l'area contiene la matrice ritorna tutta la matrice 
std::vector<AttackUnit> DefenseMap::spot_area(const Position& target_origin, int side) const 
{
    std::vector<AttackUnit> discovered_position{}; 
    // se la posizione non è corretta ritorno un vettore vuoto 
    if(!check_position(target_origin)) return discovered_position; 
    // determino il vertice di partenza 
    Position start = target_origin - Position{side/2, side/2}; 
    // inserisco per ogni casella Y se piena o unknown se vuota  
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if(check_position(start))
            {
                if(defense_map_[start.Y()][start.X()].status() == DefenseStatus::empty)
                    discovered_position.push_back(AttackUnit::unknown); 
                else discovered_position.push_back(AttackUnit::spotted);
            }
            start.set_x(start.X() + j); 
        }
        start.set_y(start.Y() + i); 
        start.set_x(target_origin.X() - side/2); 
    }
    // il vettore contirnr la matrice scritta per righe 
    return discovered_position; 
}

// funzione che ritorna se ci sono blocchi con centro uguale al target
bool DefenseMap::center_block_discovery(const Position& center_block) const 
{
    // scorro tutta la matrice e alla prima ricorrenza ritorno true
    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j < kWidth; j++)
        {
            if(defense_map_[i][j].block_center() == center_block) return true;
        }
        
    }
    return false; 
}

// funzione che permette di aggiungere una nave. 
// il primo parametro è la posizione della prua e il secondo è la poppa della nave
// ritorna true se l'operazione è andata buon fine, false se era già presente una posizione con il centro calcolato per prua e poppa
// fa inotre il check che la distanza tra prua e poppa sia effettivamente una delle 3 possibili per nave 
bool DefenseMap::add_ship(const Position& bow_position, const Position& stern_position)
{
    // controllo se le posizioni sono valide e se condividono la stessa colonna o la stessa riga 
    if(!check_position(bow_position) && !check_position(stern_position)
    && bow_position.X() != stern_position.X() && bow_position.Y() != stern_position.Y()) return false; 

    // determino centro, direzione e dimensione: 
    Position center_block = (bow_position+stern_position)/2; 

    //verifico se ci sono blocchi con lo stesso centro all'interno
    if(center_block_discovery(center_block)) return false; 

    int size; 
    Direction orientation = Direction::vertical; 

    if(bow_position.Y() == stern_position.Y()) // è in orizzontale 
    {
        orientation = Direction::horizontal; 
        size = std::abs(bow_position.X() - bow_position.X()); 
    }
    else // è in verticale
    {
        size = std::abs(bow_position.Y() - bow_position.Y()); 
    }

    // controllo che la dimensione sia ammissibile 
    if(size != kShipType1Dim && size != kShipType2Dim && size != kShipType3Dim) return false; 

    // ora provo a piazzare la nave 
    // creo la copia di prua e poppa poichè il metodo non ne garantisce la constness
    Position init = bow_position; 
    Position end = stern_position;
    return place_ship(init, end, center_block, size, orientation); 
}


// funzione che verifica se un'area è accerchiata
bool DefenseMap::is_sorrounded(const Position& target_origin, int size, Direction orientation) const
{
    if(!check_position(target_origin)) return false;
    // in base alla direzione controllo...
    if(orientation == Direction::vertical)
    {
        Position offset{0, size/2 + 1}; 

        // controllo sopra e sotto all'area che ricopre
        // se uno dei due è vuoto allora l'area non è accerchiata 
        if(check_position(target_origin - offset) && check_position(target_origin + offset))
            if(defense_map_[(target_origin - offset).Y()][(target_origin - offset).X()].status() == DefenseStatus::empty
            || defense_map_[(target_origin + offset).Y()][(target_origin + offset).X()].status() == DefenseStatus::empty) return false; 

        // ora sopra e sotto sono bloccati
        // controllo i lati 
        offset.set_x(-1); 
        offset.set_y(size/2); 
        Position checker = target_origin - offset; 
        for (int i = 0; i < size; i++)
        {
            checker.set_y(checker.Y() + i);
            // non appena ne trovo uno vuoto ritorno
            // devo controllare da entrambe i lati => sommo 2 alla x
            if(check_position(checker) && check_position(checker + Position{2,0}) && 
            (defense_map_[checker.Y()][checker.X()].status() == DefenseStatus::empty || defense_map_[checker.Y()][checker.X() + 2].status() == DefenseStatus::empty))
                return false; 
        }
    }
    else
    {
        Position offset{size/2 + 1, 0}; 

        // controllo a destra e sinistra l'area che ricopre
        // se uno dei due è vuoto allora l'area non è accerchiata 
        if(check_position(target_origin - offset) && check_position(target_origin + offset))
            if(defense_map_[(target_origin - offset).Y()][(target_origin - offset).X()].status() == DefenseStatus::empty
            || defense_map_[(target_origin + offset).Y()][(target_origin + offset).X()].status() == DefenseStatus::empty) return false; 

        // ora sopra e sotto sono bloccati
        // controllo i lati 
        offset.set_y(-1); 
        offset.set_x(size/2); 
        Position checker = target_origin - offset; 
        for (int i = 0; i < size; i++)
        {
            checker.set_x(checker.X() + i);
            // non appena ne trovo uno vuoto ritorno
            // devo controllare da entrambe i lati => sommo 2 alla x
            if(check_position(checker) && check_position(checker + Position{2,0}) && 
            (defense_map_[checker.Y()][checker.X()].status() == DefenseStatus::empty || defense_map_[checker.Y()][checker.X() + 2].status() == DefenseStatus::empty))
                return false; 
        }
    }

    return true; 
}

// Overload dell'operatore << che scrive nell'output stream la matrice di difesa
std::ostream& DefenseMap::operator<<(std::ostream& data_stream)
{
    // per ogni cella mi devo recuperare la DefenseUnit e guaradre alle informazioni che 
    // ha per determinare cosa scrivere effettitavemnte 

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
            switch (defense_map_[i][j].status())
            {
                case DefenseStatus::empty: 
                    data_stream<<" ";
                break;
                case DefenseStatus::hit:
                    // in base alla dimensione devo scrivere la lettera corretta
                    switch (defense_map_[i][j].full_block_dimension())
                    {
                        case kShipType1Dim:
                            data_stream<<kSubmarineUnitHit;
                            break;                    
                        case kShipType2Dim:
                            data_stream<<kSupportShipUnitHit;
                            break;
                        case kShipType3Dim:
                            data_stream<<kIroncladUnitHit;
                            break; 
                    }
                break;
                case DefenseStatus::taken:
                    // in base alla dimensione devo scrivere la lettera corretta
                    switch (defense_map_[i][j].full_block_dimension())
                    {
                        case kShipType1Dim:
                            data_stream<<kSubmarineUnit;
                            break;                    
                        case kShipType2Dim:
                            data_stream<<kSupportShipUnit;
                            break;
                        case kShipType3Dim:
                            data_stream<<kIroncladUnit;
                            break; 
                    }
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