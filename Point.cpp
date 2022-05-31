/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#include "Point.h"
#include <iostream>

using namespace std;

Point::Point( char newX, int newY )
{
    this->X = newX;
    this->Y = newY-1;
}

int Point::xConv()
{
    switch(this->X){
        case 'a':
            return 0;
        case 'A':
            return 0;
        case 'b':
            return 1;
        case 'B':
            return 1;
        case 'c':
            return 2;
        case 'C':
            return 2;
        case 'd':
            return 3;
        case 'D':
            return 3;
        case 'e':
            return 4;
        case 'E':
            return 4;
        case 'f':
            return 5;
        case 'F':
            return 5;
        case 'g':
            return 6;
        case 'G':
            return 6;
        case 'h':
            return 7;
        case 'H':
            return 7;
        case 'i':
            return 8;
        case 'I':
            return 8;
        case 'j':
            return 9;
        case 'J':
            return 9;
        default:
            cout <<"\nGOT TO DEFAULT";
            return -1;
    } //end switch
}


