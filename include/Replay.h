// Author: Mattia Galassi
#ifndef BATTLESHIPPROJECT_REPLAY_H_
#define BATTLESHIPPROJECT_REPLAY_H_

#include "Move.h"
#include "Utility.h"
#include <vector>
#include <fstream>

class Replay
{
public:
    class InvalidOperation : std::exception {};
    class IllegalFileLog : std::exception {};

    // Constructor that accepts the name of the log file:
    // If the class is created for reading from a file, it will open file_name for reading.
    // Otherwise, it represents the name of the log file to write to.
    Replay(std::string file_name);

    Replay();

    // Function to set the two players (in the order of parameters)
    // and the maximum number of moves representing the header of the file to write
    void record_header(std::string player1, std::string player2, int num_rounds);

    // Function to record a move in the history
    // player_name is the name of the player who made the move
    void record_move(const Move &move);

    // Overload of the previous function that accepts a string
    void record_move(std::string move);

    // Function that loads the log file into memory (buffer_) for reading
    bool open_log();

    // Function to get the first player if opening a log file for reading
    // Throws exception if the file has not been loaded yet
    std::string get_first_player_name();

    // Function to get the second player if opening a log file for reading
    // Throws exception if the file has not been loaded yet
    std::string get_second_player_name();

    // Function to get the number of rounds if opening a log file for reading
    // Throws exception if the file has not been loaded yet
    int get_number_of_rounds();

    // Function that returns the number of remaining moves in the buffer
    int get_remaining_rounds();

    // Check if a move is available in the data buffer
    bool has_next();

    // Function to get the next move from the data buffer stream
    // Returns a string to be converted to a Move
    std::string next();

    // Function to save all recorded history to a file
    // Returns true if the log was successfully written (to the file specified in the constructor)
    bool flush_recording();

    // Destructor that calls flush if it has not been done already
    ~Replay();

private:
    // Variable that stores the name of the file to create
    // Contains the full path; if not explicitly specified, the file is created in the current directory
    // If the file already exists, it is deleted and a new one is created
    std::string file_name_;
    // Vector storing all historical data to be flushed to file
    std::vector<std::string> buffer_;
    // Next move to read
    int currentTransaction;
    // Flag for flush in destructor
    bool recorded;

    // CONSTANT AREA
    static constexpr char kMarker = ' ';
    static constexpr char kLineMarker = '\n';
    static constexpr int kFirstPlayerPosition = 0;
    static constexpr int kSecondPlayerPosition = 1;
    static constexpr int kNumRoundsPosition = 2;
    static constexpr int kStartRounds = 3;
};

/* 
This class is designed to record all moves made in a game and save them to a log file.
It is also designed to read the log and show a "replay" either on screen or in a file.
The class creates the log in the log subdirectory of the current directory, creating it if it does not exist.

LOG FILE STRUCTURE AND LOCATION

The log file consists of three main parts: header, ship addition commands, and player moves.
The header includes the names of the players (in starting order) and the number of moves set at the beginning
of the game. This is followed by ship addition commands (with the same format as player moves),
and finally, the moves made in each turn.

Since the file is intended for replay mode rather than user inspection, no headers or comments are added inside the file.

Log files are automatically saved at the end of the game in the project's bin folder.
*/

#endif
