// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_GAMEMODE_H_
#define BATTLESHIPPROJECT_GAMEMODE_H_

// Enumerator that defines the type of game being played
enum GameMode
{
    PlayerVsComputer,   // Player versus computer game
    ComputerVsComputer, // Computer versus computer game
    PrintReplay,        // Replay mode that prints the log file to screen
    WriteReplay         // Replay mode that writes the log file to a file
};

#endif
