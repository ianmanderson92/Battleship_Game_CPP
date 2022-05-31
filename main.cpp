/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#include <iostream>
#include "Grid.h"
#include "PlayerGrid.h"
#include "ComputerGrid.h"

int main() {

    PlayerGrid Player =  PlayerGrid();

    try
    {
        Player.fill();
    }
    catch ( int x )
    {
        cout << "\nThe system encountered one or more error(s) while filling the "
                "\ngrid of ships.  Please resolve all errors mentioned above in order"
                "\nto play the battleship game!"
                "\n\nThe following is an INCOMPLETE GRID, and should be used to correct"
                "\nerrors ONLY!!\n";

        Player.printShips();
        return 0;
    }

    //Only continues if all ships are placed successfully.
    cout << "\nAll ships have been placed successfully!\n\n";
    Player.printShips();

    //Fills and displays the computer's grid when players grid
    //is filled successfully.
    ComputerGrid Computer = ComputerGrid();
    Computer.fill();

    cout<< "\nCOMPUTER's GRID:  \n";
    Computer.printShips();

    //Code for the Main Game
    cout << "\n=========================INSTRUCTIONS====================="
            "\nYou will be asked to enter coordinates where the torpedo should be fired!!"
            "\nHits are displayed with 'O's"
           "\nMisses are displayed with 'X's"
           "\n\nThe computer player will fire torpedoes after you,"
           "\nand then you will be able to view both grids."
           "\n\nOnly one torpedo hit will sink an entire ship."
           "\n\nEnter 'Q' as your x coordinate in order to quit the game."
           "\n=========================================================\n";

    //For game victory, 0 denotes unfinished, 1 denotes player victory, 2 denotes computer victory.
    bool gameVictory = false;

    //Main game loop that continues until someone wins
    while( gameVictory == false )
    {
        //Take in user input and convert it to a "Point"
        //while checking for input validity.
        try
        {
            Player.guess( Computer );
        } catch ( int x )
        {
            cout << "\nThanks for playing!! . . . but quitters never win.";
            return 0;
        }
        gameVictory = Computer.victoryDetection();
        if ( gameVictory )
        {
            cout << "\nComputer's Guess Grid: \n";
            Computer.printGuess();
            cout << "\nPlayer ONE Grid: \n";
            Player.printGuess();
            break;
        }

        Computer.guess( Player );
        gameVictory = Player.victoryDetection();

        if ( gameVictory )
        {
            cout << "\n\nComputer's Guess Grid: \n";
            Computer.printGuess();
            cout << "\nPlayer ONE Grid: \n";
            Player.printGuess();
            break;
        }

        cout << "\nComputer's Guess Grid: \n";
        Computer.printGuess();

        cout << "\nPlayer ONE Grid: \n";
        Player.printGuess();
    } // END WHILE
    return 0;
} //end of main()