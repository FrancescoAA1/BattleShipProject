#include "Ironclad.h"

//Per eseguire la sua azione di attacco, la nave corazzata ha bisogno dei seguenti dati:
//La mappa di attacco del giocatore che ordina la mossa, la quale verrà modificata
//La posizione obiettivo dell'attacco
//La nuova attack unit modificata da sostituire nella mappa di attacco ricevuta, alla posizione target 
//sebbene la attack unit da ricevere sia una sola, viene utilizzato un array per conformare i metodi action di tutte le navi
//
//i controlli sulla validità della mossa sono già stati effettuati, e la nave può quindi procedere con sicurezza all'azione
void Ironclad::action(Map& map, const Position& target, const std::vector<AttackUnit>& data)
{
    //copia la attack unit ricevuta nella mappa di attacco alle coordinate ricevute
    map.attack_map()[target.x()][target.y()] = data.at(0);
}