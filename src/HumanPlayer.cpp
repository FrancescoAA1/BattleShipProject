#include "../include/HumanPlayer.h"


HumanPlayer::HumanPlayer(const std::string& nickname) : Player(nickname)
{
}

Move HumanPlayer::get_move(const std::string& move)
{
    //da implementare
    //controllo subito che la stringa sia AA AA
    //se è cosi
    Position origin{};
    Position target{};

    if(move == "AA AA")
    {
        origin.make_absolute_invalid();
        target.make_absolute_invalid();
        return Move{origin, target, MoveType::showMap};
    }
    else if(move == "YY YY")
    {
        origin.make_absolute_invalid();
        target.make_absolute_invalid();
        return Move{origin, target, MoveType::clearMap};
    }
    else
    {
        char originX = move[0] - defaultCapitalAscii;
        char originY = move[1] - 1;

        char targetX = move[3] - defaultCapitalAscii;
        char targetY = move[4] - 1;

        if((originX >= 0 || originX <= 11) && (originX >= 0 || originX <= 11))
        {
            origin = {originX, originY};
        }
        else
        {
            throw InvalidMove{};
        }

        Ship* shipMove = sea_map_.get_ship(origin);
        shipMove

    }

    //altrimenti controllo che la stringa sia YY YY


    //altrimenti separo la stringa in due parti
    
    //considero la prima stringa e prendo il primo carattere
    //converto quest'ultimo sottraendo al suo valore ASCII il valore 65 (da aggiungere come costante nella classe Player?)
    //infatti 'A' - 65 = 0 (posizione X)
    //tolgo 1 al secondo carattere per avere corrispondenza con gli indice della matrice della mappa
    //se posizione x e posizione y sono comprese tra 0 e 11
    //allora procedo con la creazione di una posizione

    //ripeto la procedura precedente per la seconda parte della stringa

    //se una delle due coordinate non vanno bene restituisco eccezione invalidmove

    //ottengo così le due coordinate, ma necessito ancora del tipo di nave

    //richiedo la nave alla mappa con getship(origin, target, nullptr)
    //creo la mossa con tipo di nave e la ritorno


    
}