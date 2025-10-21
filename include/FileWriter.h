// Author: Mattia Galassi 
#ifndef BATTLESHIPPROJECT_FILEWRITER_H_
#define BATTLESHIPPROJECT_FILEWRITER_H_

#include <vector>
#include <fstream>
#include <string>

class FileWriter
{

public:
    // Constructor that accepts the file name where to write:
    FileWriter(std::string file_name);

    FileWriter();

    // Function that allows writing a string to the buffer
    void write_line(std::string line);

    // Function that saves the entire buffer to the file
    // Returns true if the file was successfully written -> the file created is the one specified
    // in the constructor
    // Returns false if the process failed
    bool flush_recording();

    // Destructor that invokes flush if it was not already done
    ~FileWriter();

private:
    // Variable that stores the name of the file to create
    // It contains the full path, and if not explicitly specified, it creates the file in the current directory
    // If the file already exists, it deletes it and creates a new one
    std::string file_name_;
    // Vector where all history is stored, then flushed to the file
    std::vector<std::string> buffer_;

    // Flag to track if flush has been done in the destructor
    bool recorded;

    static constexpr char kLineMarker = '\n';
};

// This class is meant to wrap the file object and allow writing strings to it
// The actual file writing happens during flush to avoid keeping the resource open for the entire program execution
// If the object is destroyed without ever invoking flush, it performs it by default in the destructor
#endif
