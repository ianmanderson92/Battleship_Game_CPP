/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#ifndef FINAL_PROJECT_BATTLESHIP_POINT_H
#define FINAL_PROJECT_BATTLESHIP_POINT_H


class Point{

public:
    char X;
    int Y;
    Point( char newX, int newY );
    int xConv();
};


#endif //FINAL_PROJECT_BATTLESHIP_POINT_H
