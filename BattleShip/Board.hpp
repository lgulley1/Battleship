//
//  Board.hpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include "Ship.hpp"

class Board {
private:
    std::vector<Ship> shipsOnBoard;
    std::vector<int> spacesFiredUpon;
public:
    Board() {}
    Board(const Board &rhs);
    Board& operator=(const Board &rhs);
    void addShip(Ship);
    bool isAllSunk(); //checks if all ships on board are sunk
    void print(bool);
    bool rangeIsValid(int, int); //returns true if  range is within board's border
    bool rangeIsOccupied(int, int); //returns true if range already contains a ship
    bool isValidAttack(int); //returns true if range is valid and range is not occupied
    Ship getShipByCoord(int); //returns Ship on board based on it's coordinate
    void fire(int attackCoord) { spacesFiredUpon.push_back(attackCoord); } //fires at a coordinate
    bool shipSunk(int shipCoord); //returns true if ship on coordinate is sunk
    void sinkShip(int attackCoord); //sinks ship based on location
    bool beenHit(int); //returns true if a space has already been fired upon
    //checks open space available starting from a coordinate
    //used to see if ship can fit, for targeting algorithm
    int getFreeVSpace(int);
    int getFreeHSpace(int);
};

#endif /* Board_hpp */
