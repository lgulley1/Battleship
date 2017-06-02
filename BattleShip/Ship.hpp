//
//  Ship.hpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

const std::string border = "-------------------------------------------"; //formatting

class Ship {
private:
    std::vector<int> shipRange;
    std::string name = "";
    bool sunk = false;
public:
    Ship(std::string, int, int); //create ship
    int getSize();
    std::string getName() { return name; }
    bool isSunk() { return sunk; }
    bool containsShip(int); //searches shipRange to check if a ship contains a specific coordinate
    void sink() { sunk = true; } //sink ship
    bool operator==(const Ship&) const;
};

#endif /* Ship_hpp */
