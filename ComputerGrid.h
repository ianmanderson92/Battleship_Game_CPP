/*
NAME: Ian Anderson
DATE: December 3rd, 2019
CLASS: CSCI 2312
DESCRIPTION: Battleship Game
STATUS: Fully Operational
*/

#ifndef FINAL_PROJECT_BATTLESHIP_COMPUTERGRID_H
#define FINAL_PROJECT_BATTLESHIP_COMPUTERGRID_H

#include "Grid.h"

using namespace std;


class ComputerGrid : public Grid {

public:
    virtual void fill();
    virtual void guess( Grid& opponentGrid );
    virtual bool victoryDetection();

};


#endif //FINAL_PROJECT_BATTLESHIP_COMPUTERGRID_H
