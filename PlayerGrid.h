/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#ifndef FINAL_PROJECT_BATTLESHIP_PLAYERGRID_H
#define FINAL_PROJECT_BATTLESHIP_PLAYERGRID_H

#include "Grid.h"
#include <string>

using namespace std;

class PlayerGrid : public Grid {

public:
    virtual void fill();
    virtual void guess( Grid& opponentGrid );
    virtual bool victoryDetection();

private:
    const string fileName ="ship_placement.csv";
    bool fileValidityCheck();

};


#endif //FINAL_PROJECT_BATTLESHIP_PLAYERGRID_H
