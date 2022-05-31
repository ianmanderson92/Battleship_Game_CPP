/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/
#include <vector>
#include <string>
#include "Point.h"
using namespace std;

#ifndef FINAL_PROJECT_BATTLESHIP_GRID_H
#define FINAL_PROJECT_BATTLESHIP_GRID_H


class Grid {
protected:
    //modular variables for grid size.
    const int BoardHeight = 10;
    const int BoardWidth = 10;

    vector < vector<int> > gridVect;
    vector < vector<int> > guessVect;

public:
    Grid();
    void printShips() { printGrid( false );}
    void printGuess() { printGrid( true );}
    virtual void fill() = 0;
    virtual void guess( Grid& opponentGrid ) = 0;
    virtual bool victoryDetection() = 0;


protected:
    void printGrid( bool isGuessGrid );
    bool addShiptoGrid( int shipSize, Point topPoint, char direction , bool player, int shipNum );
    int hitDetection( Grid& opponentGrid, Point guessPoint );
    bool victoryDetection( bool player );

    //helper functions
    int shipTypetoNum( string shipType );
    string NumtoShipType( int shipSize );
    int CharToInt( const char c);
    char InttoChar( const int i );


};


#endif //FINAL_PROJECT_BATTLESHIP_GRID_H
