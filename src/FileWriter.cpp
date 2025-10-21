// Author: Mattia Galassi
#include "../include/FileWriter.h"

// Constructor that accepts the file name where data will be written
FileWriter::FileWriter(std::string file_name)
{
    file_name_ = file_name;
    recorded = false;
    buffer_ = std::vector<std::string>();
}

// Default constructor
FileWriter::FileWriter()
{
    file_name_ = ".txt"; // default file name
    recorded = false;
    buffer_ = std::vector<std::string>();
}

// Adds a line to the internal buffer
void FileWriter::write_line(std::string line)
{
    buffer_.push_back(line);
}

// Writes the entire buffer to the file
// Returns true if writing was successful, false otherwise
bool FileWriter::flush_recording()
{
    // if buffer is empty, nothing to write
    if (buffer_.empty())
        return false;

    std::ofstream file;

    try
    {
        file = std::ofstream(file_name_);

        for (int i = 0; i < buffer_.size(); i++)
        {
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

// Destructor ensures that any remaining buffer is written to file
FileWriter::~FileWriter()
{
    if (!recorded && !buffer_.empty())
        flush_recording();
}
