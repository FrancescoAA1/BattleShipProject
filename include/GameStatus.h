//Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_GAMESTATUS_H_
#define BATTLESHIPPROJECT_GAMESTATUS_H_

//enumeratore che definisce lo stato della partita
enum GameStatus
{
    Ongoing, //partita non terminata
    Player1Won, //giocatore 1 ha vinto
    Player2Won,//giocatore2 ha vinto
    Tie //pareggio
};

#endif