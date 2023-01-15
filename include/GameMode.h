#ifndef BATTLESHIPPROJECT_GAMEMODE_H_
#define BATTLESHIPPROJECT_GAMEMODE_H_

//enumeratore che definisce la tipologia di partita iniziata
enum GameMode
{
    PlayerVsComputer, //partita giocatore contro computer
    ComputerVsComputer, //partita computer contro computer
    PrintReplay, //modalità replay di stampa a video del file di log
    WriteReplay //modalità replay di scrittura del log su file
};

#endif