// Author: Mattia Galassi
#include "../include/Replay.h"

// Constructor that accepts the name of the log file as a parameter:
// if the class is created for reading from a file, it will open file_name in read mode
// otherwise it represents the name of the log file to write
Replay::Replay(std::string file_name)
{
    // initialize class variables
    file_name_ = file_name;
    buffer_ = std::vector<std::string>();
    recorded = false;
}

Replay::Replay()
{
    file_name_ = "log.txt";
    buffer_ = std::vector<std::string>();
    recorded = false;
}

// function to set the two players (in the order of parameters)
// and the maximum number of moves, representing the header to write
void Replay::record_header(std::string player1, std::string player2, int num_rounds)
{
    // if buffer is already full, create a new one to maintain correct writing standard
    if (!buffer_.empty())
        buffer_ = std::vector<std::string>();

    buffer_.push_back(player1);
    buffer_.push_back(player2);
    buffer_.push_back(std::to_string(num_rounds));
}

// function to record a move in the history
// player_name is the name of the player who made the move
void Replay::record_move(const Move &move)
{
    // if the header has not been written yet, throw exception
    if (buffer_.size() < 3)
        throw InvalidOperation();

    buffer_.push_back(move.to_string());
}

// overload of the previous function that accepts a string
void Replay::record_move(std::string move)
{
    // if the header has not been written yet, throw exception
    if (buffer_.size() < 3)
        throw InvalidOperation();

    buffer_.push_back(move);
}

// function to save the entire recorded history to a file
// returns true if the log was successfully written -> the file created is the one specified
// in the constructor
// false if the process failed
bool Replay::flush_recording()
{
    // if the recording history is empty, return false
    if (buffer_.empty())
        return false;
    std::ofstream file;
    // otherwise, write all elements of recording_
    try
    {
        file = std::ofstream(file_name_);
        for (int i = 0; i < buffer_.size(); i++)
        {
            // if it's the last one, do not add \n
            if (i == buffer_.size() - 1)
                file << buffer_[i];
            else
                file << buffer_[i] << kLineMarker;
        }

        file.close();

        recorded = true;

        return true;
    }
    catch (const std::exception &e)
    {
        file.close();
        return false;
    }
    return false;
}

// function that loads the log file used to construct the object into memory (buffer_)
// returns false if the file does not exist or if something goes wrong during reading
bool Replay::open_log()
{
    // if the recording history is not empty, create a new one
    if (!buffer_.empty())
        buffer_ = std::vector<std::string>();

    std::ifstream file;
    // open the file and read all lines into the buffer
    try
    {
        file = std::ifstream(file_name_);
        std::string tmp;

        while (getline(file, tmp))
        {
            buffer_.push_back(tmp);
        }

        file.close();
        // prepare the cursor for moves
        currentTransaction = kStartRounds;
        return true;
    }
    catch (const std::exception &e)
    {
        file.close();
        return false;
    }
    return false;
}

// function to get the first player when opening a log file
// throws exception if the file has not been loaded yet
std::string Replay::get_first_player_name()
{
    // if buffer is empty, the file was not loaded or is invalid
    if (buffer_.size() < kFirstPlayerPosition + 1)
        throw InvalidOperation();

    return buffer_[kFirstPlayerPosition];
}

// function to get the second player when opening a log file
// throws exception if the file has not been loaded yet
std::string Replay::get_second_player_name()
{
    // if buffer is empty, the file was not loaded or is invalid
    if (buffer_.size() < kSecondPlayerPosition + 1)
        throw InvalidOperation();

    return buffer_[kSecondPlayerPosition];
}

// function to get the number of rounds when opening a log file
// throws exception if the file has not been loaded yet
int Replay::get_number_of_rounds()
{
    // if buffer is empty, the file was not loaded or is invalid
    if (buffer_.size() < kNumRoundsPosition + 1)
        throw InvalidOperation();

    return std::stoi(buffer_[kNumRoundsPosition]);
}

// check if a move is available in the data buffer
bool Replay::has_next()
{
    return currentTransaction < buffer_.size();
}

// function that returns the number of remaining moves in the buffer
int Replay::get_remaining_rounds()
{
    if (buffer_.size() >= kNumRoundsPosition + 1)
        return buffer_.size() - currentTransaction;
    else
        return 0;
}

// function to get the next move from the data buffer stream
// returns a string to convert to a move
std::string Replay::next()
{
    if (!has_next())
        throw InvalidOperation();

    return buffer_[currentTransaction++];
}

// destructor that invokes flush if it has not been performed
// previously
Replay::~Replay()
{
    if (!recorded && !buffer_.empty())
        flush_recording();
}
