//
//  Ship.cpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#include "Ship.hpp"

Ship::Ship(std::string nName, int head, int tail) {
    name = nName;
    
    while(head != tail) {
        shipRange.push_back(head);
        if(head%10 == tail%10) { //if same y coord
            if(head > tail) {
                head -= 10;
            }
            else {
                head += 10;
            }
        }
        else {
            if(head > tail) {
                head--;
            }
            else {
                head++;
            }
        }
    }
    shipRange.push_back(head);
}

int Ship::getSize() {
    return static_cast<int>(shipRange.size());
}

bool Ship::containsShip(int coord) {
    for(size_t i = 0; i < shipRange.size(); i++) {
        if(shipRange[i] == coord) { return true; }
    }
    return false;
}

bool Ship::operator==(const Ship &rhs) const {
    if((name != rhs.name) || (sunk != rhs.sunk)) {
        return false;
    }
    
    for(size_t i = 0; ((i < shipRange.size()) && (i < rhs.shipRange.size())); i++) {
        if(shipRange[i] != rhs.shipRange[i]) {
            return false;
        }
    }
    return true;
}
