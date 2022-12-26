#ifndef BATTLESHIPPROJECT_SHIP_H_
#define BATTLESHIPPROJECT_SHIP_H_

//enumeratore che definisce la direzione di una nave (orizzontale o verticale)
enum Direction
{
    horizontal,
    vertical
};

class Ship
{
    public:

        //disattivo il costruttore di copia per rendere la classe astratta
        Ship(const Ship&) = delete;
        //disattivo l'assegnamento di copia per rendere la classe astratta
        Ship& operator=(const Ship&) = delete;

        //metodo virtuale che definisce l'azione che può eseguire la nave (attacco, spostamento e cura, spostamento e ispezione)
        //e' necessario implementarlo in maniera diversa in ognuna della classi nave derivate
        virtual void action(Map attack_map, Map defense_map, Position target) = 0;

        //metodi getter
        int armor() const {return armor_;}
        int size() const {return size_;}
        Direction orientation() const {return orientation_;}
        
        //la nave è stata colpita: riduce la corazza di 1
        void hit();
        //la nave è stata curata da una nave di supporto: ripristina la corazza al valore iniziale
        void restore();


    protected:

        //costruttore, richiede la dimensione della nave e il suo orientamento
        Ship(int, Direction);
    

    private:

        //variabile che definisce la direzione secondo cui è orientata la nave
        Direction orientation_;
        //variabile che indica la corazza attuale della nave
        int armor_;
        //variabile che definisce la dimensione della nave
        int size_;

}; 

/*
Classe Ship: rappresenta una nave generica a disposizione del giocatore
La classe è astratta e da essa derivano 3 sotto-classi, una per ogni tipo di nave nel gioco
Il punto fondamentale della classe è il metodo action()
*/

#endif