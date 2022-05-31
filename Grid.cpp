/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#include "Grid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

//default constructor, initialized whole grid with '0's
Grid::Grid()
{
    vector< vector<int> > g;
    vector< vector<int> > h;
    for( int i=1; i <= BoardHeight; i++ )
    {
        vector<int> g1;
        vector<int> h1;
        for( int j=1; j <= BoardWidth; j++ )
        {
            //fills array with '0's
            g1.push_back(0);
            h1.push_back(0);
        }
        g.push_back(g1);
        h.push_back(h1);
    }
    gridVect = g;
    guessVect = h;
} //end Grid

//prints the grid to the console
void Grid::printGrid( bool isGuessGrid )
{
    int yCoorIndicator = 1;
    string spacerline = "    ~~~~~~~~~~~~~~~~~~~\n";
    string xCoorIndicator = "    A B C D E F G H I J\n";

    cout << xCoorIndicator;
    cout << spacerline;
    for( int i=0; i < BoardHeight; i++)
    {
        if ( yCoorIndicator <  10 )
        {
            cout << yCoorIndicator << "   ";
        } else
        {
            cout << yCoorIndicator << "  ";
        }
        yCoorIndicator++;

        for(int j=0; j < BoardWidth; j++ )
        {
            int currentSpot = ( isGuessGrid ? guessVect : gridVect )[i][j];
            //Convert 9s and 8s to 'O's and 'X's respectively
            // 'O's denote a successful hit, 'X's denote a miss
            if ( currentSpot == 0 )
            {
                cout << '.' << " ";
            }
            else if( currentSpot == 9 )
            {
                cout << 'O' << " ";
            } else if ( currentSpot == 8 )
            {
                cout << 'X' << " ";
            }else {
                cout << currentSpot << " ";
            }
        } //end for
        cout << endl;
    } //end for
    cout << spacerline;
} //end printGrid

//Used to add ship to grid with passed in info, will display error messages if player = true.
bool Grid::addShiptoGrid( int shipSize, Point topPoint, char direction , bool player, int shipNum )
{
    //HORIZONTAL DIRECTION
    if ( direction == 'H' )
    {
        int xCoor = topPoint.xConv();
        int yCoor = topPoint.Y;

        //Error checking for grid placement overflow.
        try
        {
            if( (xCoor + (shipSize)) >= 11 ) throw 4;
        }
        catch (int x)
        {
            if( player == true )
            {
                cout << "\nPlacement of the ship mentioned above doesn't fit on the grid."
                        "\nPlease rearrange your ships and try again."
                     << "\nERROR CODE: " << x << endl;
            }
            return false;
        }
        int TempXCoor = xCoor;
        for ( int i=0; i< shipSize; i++ )
        {
            //Error checking to check for overlapping ships
            try
            {
                if ( gridVect[yCoor][TempXCoor++] != 0 ) throw 5;
            }
            catch (int x)
            {
                if( player == true )
                {
                    cout << "\nThe ship mentioned above appears to overlap with another ship."
                            "\nPlease rearrange the ships and try again"
                         << "\nERROR CODE: " << x << endl;
                }
                return false;
            }
        }
        for ( int i=0; i< shipSize; i++ )
        {
            gridVect[yCoor][xCoor++] = shipNum;
        }
        return true;
    //VERTICAL DIRECTION
    } else if ( direction == 'V' )
    {
        int xCoor = topPoint.xConv();
        int yCoor = topPoint.Y;
        //Error checking for placement overflow
        try
        {
            if( (yCoor + (shipSize)) >= 11 ) throw 4;
        }
        catch (int x)
        {
            if( player == true )
            {
                cout << "\nPlacement of the ship mentioned above doesn't fit on the grid."
                        "\nPlease rearrange your ships and try again."
                     << "\nERROR CODE: " << x << endl;
            }
            return false;
        }
        int TempYCoor = yCoor;
        for ( int i=0; i< shipSize; i++ )
        {
            //Error checking to check for overlapping ships
            try
            {
                if ( gridVect[TempYCoor++][xCoor] != 0 ) throw 5;
            } //end try
            catch (int x)
            {
                if( player == true )
                {
                    cout << "\nThe ship mentioned above appears to overlap with another ship."
                            "\nPlease rearrange the ships and try again"
                         << "\nERROR CODE: " << x << endl;
                }
                return false;
            }
        } //End for
        for ( int i=0; i< shipSize; i++ )
        {
            gridVect[yCoor++][xCoor] = shipNum;
        }
        return true;
    } //end if/else
    return false;
}//end addShiptoGrid

int Grid::hitDetection( Grid& opponentGrid, Point guessPoint )
{
    int xCoor = guessPoint.xConv();
    int yCoor = guessPoint.Y;
    int CurrentSpot = opponentGrid.gridVect[yCoor][xCoor];

    //if the torpedo is not empty
    if ( CurrentSpot == 0 )
    {
        guessVect[yCoor][xCoor] = 8;
        opponentGrid.gridVect[yCoor][xCoor] = 8;
        return 0;
    }
    if ( CurrentSpot >= 1 && CurrentSpot <= 5 )
    {
        //iterate through whole board and turn all ship tiles to denote a hit on both the
        // original grid and the guessGrid.
        for( int i=0; i < BoardHeight; i++)
        {
            for( int j=0; j < BoardWidth; j++ )
            {
                if( opponentGrid.gridVect[i][j] == CurrentSpot )
                {
                    //Changes grid value to 9 with denotes a hit and will
                    // be converted in the printGrid() function.
                    guessVect[i][j] = 9;
                    opponentGrid.gridVect[i][j] = 9;
                }
            }
        }
        return CurrentSpot;
    }
    return 6;
} //End hitDetection()

bool Grid::victoryDetection( bool player )
{
    for( int i=0; i < BoardHeight; i++)
    {
        for(int j=0; j < BoardWidth; j++ )
        {
            if( this->gridVect[i][j] !=0 && this->gridVect[i][j] < 8 )
            {
                return false;
            }
        }
    }
    if (!player)
    {
        cout << "\n\nCongratulations!!  You are the victor of this match."
                "\nAll of the computer player's ships have been sunk!\n";
        return true;
    }
    else
    {
        cout << "\n\nThe computer player has defeated you and sunken all of your battleships!"
                "\nBetter luck next time!\n";
        return true;
    }
} //End victoryDetection


int Grid::shipTypetoNum( string shipType )
{
    if ( shipType == "Carrier" )
    {
        return 5;
    }
    if ( shipType == "Battleship" )
    {
        return 4;
    }
    if ( shipType == "Cruiser" )
    {
        return 3;
    }
    if ( shipType == "Submarine" )
    {
        return 3;
    }
    if ( shipType == "Destroyer" )
    {
        return 2;
    }
    return -1;
} //end shipTypetoNum.

string Grid::NumtoShipType(int shipSize) {
    switch ( shipSize )
    {
        case 5:
            return "Destroyer";
        case 4:
            return "Submarine";
        case 3:
            return "Cruiser";
        case 2:
            return "Battleship";
        case 1:
            return "Carrier";
        default:
            return "";
    }
} //end NumtoShipType.


int Grid::CharToInt(const char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 0;
        //return ( c >= '0' && c <= '9' ) ? c - '0' : 0 ;
    }
} //end CharToInt

char Grid::InttoChar(const int i) {
    switch (i)
    {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
        case 4:
            return 'E';
        case 5:
            return 'F';
        case 6:
            return 'G';
        case 7:
            return 'H';
        case 8:
            return 'I';
        case 9:
            return 'J';
        default:
            return 0;
    }
}//end InttoChar




