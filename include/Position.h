// Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_POSITION_H_
#define BATTLESHIPPROJECT_POSITION_H_

#include <limits.h>
#include <ostream>
#include <string>

class Position
{

public:
    // Initialize to position (0,0)
    Position();
    // Initialize to the specified position
    Position(int x, int y);

    // Return the x-coordinate
    int X() const { return x_; } 
    // Return the y-coordinate
    int Y() const { return y_; } 
    // Set the x-coordinate
    void set_x(int value); 
    // Set the y-coordinate
    void set_y(int value);
    // Set the coordinate as invalid
    void make_absolute_invalid(); 
    // Check if a coordinate is absolutely invalid
    bool is_absolute_invalid();

    // Convert the position to a string
    std::string to_string() const;  

private: 
    int x_; 
    int y_;

    static constexpr int INVALID_X_POSITION = INT_MIN; 
    static constexpr int INVALID_Y_POSITION = INT_MIN; 

};

// Operators to overload
Position operator+(const Position& p1, const Position& p2); 
Position operator-(const Position& p1, const Position& p2);
Position operator*(const Position& p, int coeff);  
Position operator/(const Position& p, int coeff);  
bool operator==(const Position& p1, const Position& p2);
bool operator!=(const Position& p1, const Position& p2);  

// Copy and move operators and constructors are not needed as no dynamic memory is allocated
std::ostream& operator<<(std::ostream& data_stream,  const Position& pos); 

#endif
