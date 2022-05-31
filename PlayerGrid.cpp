/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#include "PlayerGrid.h"
#include <iostream>
#include <fstream>

using namespace std;

void PlayerGrid::fill()
{
    bool success = fileValidityCheck();
    if ( success == false ) throw 3;

    //Varibales used to take in user input.
    string shipType;
    string shipCoor;
    string shipDir;

    int shipLength;
    char xCoor;
    char yCoor;
    int yCoorConverted;
    char direction;

    //open input file and get input.
    cout << "\nLoading from file: " << fileName << endl;
    ifstream inFile( fileName );
    if ( inFile.is_open() )
    {
        for ( int i = 0; i< 5; i++)
        {
            //get ship details from the input file.
            getline(inFile, shipType, ',');
            getline(inFile, shipCoor, ',');
            getline(inFile, shipDir, '\n');
            cout << "\nShip Type: " << shipType;
            cout << "\n( Displayed with '" << (i+1) << "'s )";
            cout << "\nShip Coor: " << shipCoor;
            cout << "\nShip Direction: " << shipDir;
            cout << endl;

            //convert strings to proper types.
            xCoor = shipCoor.at(0);
            yCoor = shipCoor.at(1);
            direction = shipDir.at(0);

            //add the ship to the grid.
            if ( shipCoor.size() == 3 ) yCoorConverted = 10;
            else yCoorConverted = CharToInt( yCoor );
            shipLength = shipTypetoNum( shipType );
            Point newPoint( xCoor, yCoorConverted );
            success = this->addShiptoGrid( shipLength, newPoint, direction, true, (i+1) );
            if ( success == false ) throw 3;
        }
    } else
    {
        cout << "\nProblem opening the input file!\n";
        throw 3;
    }
}


//Used to check if all five ships are included in the file, and if all info provided is valid.
bool PlayerGrid::fileValidityCheck() {

    //Check to make sure there are 5 ships
    int numLines = 0;
    ifstream inFile( fileName );
    if ( inFile.is_open() == false )
    {
        cout << "\nThe input file \"ship_placement.csv\" could not be opened."
                "\nPlease make sure the file is appropriately named and is located"
                "\nin the correct directory\n";
        return false;
    }
    string unused;
    while ( getline(inFile, unused) )
    {
        if( unused.empty() == false )++numLines;
    }
    if (numLines != 5)
    {
        cout << "\nThere are an incorrect number of ships in the input file."
                "\nPlease make sure all ships are represented in the input file"
                "\nERROR CODE: 3\n";
        return false;
    }
    inFile.close();

    string shipType;
    string shipCoor;
    string shipDir;
    ifstream inFile2( fileName );
    if ( inFile2.is_open() )
    {
        for ( int i = 0; i< 5; i++)
        {
            //get ship details from the input file.
            getline(inFile2, shipType, ',');
            getline(inFile2, shipCoor, ',');
            getline(inFile2, shipDir, '\n');

            if ( shipCoor.size() < 2 || shipCoor.size() > 3 )
            {
                cout << "\nOne or more ship coordinates are in the wrong format."
                        "\nPlease double check ship coordinates and try again!"
                        "\nERROR CODE: 2\n";
                return false;
            }

            if ( shipDir.size() != 1 )
            {
                cout << "\nOne or more ship direction characters is in the wrong format."
                        "\nPlease double check your ship's direction char and try again!"
                        "\nERROR CODE: 2\n";
                return false;
            }
        } //end for
        return true;
    } else
    {
        cout << "\nProblem opening the input file!\n";
    }
    return false;
}

void PlayerGrid::guess( Grid& opponentGrid )
{
    int result;
    do {
        char tempXCoor;
        int yCoor;
        bool correctInput = false;
        cout << "\n\nYour turn to guess!!";
        //get user's x Coordinate and check validity.
        do {
            cout << "\nEnter X coordinate (A-J):";
            cin >> tempXCoor;
            if ((tempXCoor >= 'a' && tempXCoor <= 'j') || (tempXCoor >= 'A' && tempXCoor <= 'J')) {
                correctInput = true;
            } else if (tempXCoor == 'Q' || tempXCoor == 'q') throw 0;
            else {
                cout << "\nPlease input a single letter from A-J"
                        "\nYour input was the incorrect format.\n";
            }
        } while (!correctInput);

        //Get user's Y coordinate and check validity.
        correctInput = false;
        do {
            cout << "Enter Y coordinate (1-10): ";
            cin >> yCoor;
            if (yCoor > 0 && yCoor < 11) correctInput = true;
            else {
                cout << "\nPlease input a single number from 1-10"
                        "\nYour input was the incorrect format\n";
                cin.clear();
                cin.ignore();
            }
        } while (!correctInput);


        Point guessPoint = Point(tempXCoor, yCoor);
        result = hitDetection( opponentGrid, guessPoint);
        if ( result == 6 )
        {
            cout << "\nLooks like you have already fired a torpedo at that spot!!";
        }
    } while ( result == 6 );
    if ( result == 0 )
    {
        cout << "\nYour shot was a miss!!";
        return;
    }
    cout << "\nYour shot was a hit!! " << NumtoShipType( result ) << " was sunk, good job.";
}

bool PlayerGrid::victoryDetection() {
    return Grid::victoryDetection( true );
}
