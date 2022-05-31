/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#include "ComputerGrid.h"
#include <time.h>
#include <iostream>

using namespace std;

void ComputerGrid::fill()
{
    srand(time(NULL));

    cout << "\nNow filling the computer's grid with ships"
            "\nin random locations.\n";

    int shipSize[5] = {5, 4, 3, 3, 2};
    int index=0;
    do{
        //random Coordinate
        char xRand = InttoChar(rand() % 10);
        int yRand = ((rand() % 10)+1);
        Point randPoint = Point(xRand, yRand);

        //Random Direction
        char randDir;
        if ((rand() % 2) == 1) randDir = 'V';
        else randDir = 'H';

        if ( addShiptoGrid(shipSize[index], randPoint, randDir, false, (index+1)) == true )
        {
            //FIXME: uncomment to see Computer's ship locations.
            /*cout << "\nShip Num: " << (index+1);
            cout << "\nShip Size: " << shipSize[index];
            cout << "\nShip Coor: " << xRand << yRand;
            cout << "\nShip Direction: " << randDir;
            cout << endl;*/
            index++;
        }

    } while( index < 5 );
}

void ComputerGrid::guess( Grid& opponentGrid )
{
    int result;
    do
    {
        char xRand = InttoChar(rand() % 10);
        int yRand = ((rand() % 10)+1);
        Point randPoint = Point(xRand, yRand);
        result = hitDetection( opponentGrid, randPoint );
    } while( result == 6 );
    if ( result == 0 )
    {
        cout << "\nThe Computer shot and missed!!\n";
        return;
    }
    cout << "\nThe Computer hit your " << NumtoShipType(result) << " and sunk it!\n";
}

bool ComputerGrid::victoryDetection() {
    return Grid::victoryDetection( false );
}
