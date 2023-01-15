//Author: Enrico Disarò
#ifndef BATTLESHIPPROJECT_POSITION_H_
#define BATTLESHIPPROJECT_POSITION_H_

#include <limits.h>
#include <ostream>

class Position
{

    public:
    //inizializzo alla posizione (0,0)
    Position();
    //inizializzo alla posizione inserita
    Position(int x, int y);

    //ritorno l'ascissa
    int X() const { return x_; } 
    //ritorno l'ordinata
    int Y() const { return y_; } 
    //imposto l'ascissa
    void set_x(int value); 
    //imposto l'ordinata
    void set_y(int value);
    //imposto la coordinata a invalida
    void make_absolute_invalid(); 
    //verifico se una coordinata è assolutamente invalida
    bool is_absolute_invalid();

    std::string to_string() const;  

    private: 
    int x_; 
    int y_;

    static constexpr int INVALID_X_POSITION = INT_MIN; 
    static constexpr int INVALID_Y_POSITION = INT_MIN; 

};
//operatori di cui fare l'overload
Position operator+(const Position& p1, const Position& p2); 
Position operator-(const Position& p1, const Position& p2);
Position operator*(const Position& p, int coeff);  
Position operator/(const Position& p, int coeff);  
bool operator==(const Position& p1, const Position& p2);
bool operator!=(const Position& p1, const Position& p2);  
//non sono necessari operatori di copia, spostamento e relativi contruttori non avendo memoria dinamica allocata
std::ostream& operator<<(std::ostream& data_stream,  const Position& pos); 
#endif