//
//  Board.cpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#include "Board.hpp"
#include <algorithm>
#include <vector>

void Board::addShip(Ship nShip) {
    shipsOnBoard.push_back(nShip);
}

bool Board::isAllSunk() {
    for(size_t i = 0; i < shipsOnBoard.size(); i++) {
        if(!shipsOnBoard[i].isSunk()) {
            return false;
        }
    }
    return true;
}

void Board::print(bool showShips) {
    std::cout << border;
    std::cout << "\n1. = - free space\n2. o - ship afloat\n3. x - hit ship\n4. n - fired upon\n";
    std::cout << border << "\n";
    std::cout << "    |A| |B| |C| |D| |E| |F| |G| |H| |I| |J|\n";
    bool shot, onBoard;
    for(int i = 0; i < 100; i++) {
        if(i%10 == 0) { std::cout << i/10 << "  - "; }
        onBoard = false;
        shot = false;
        for(size_t r = 0; r < shipsOnBoard.size(); r++) {
            if(!shipsOnBoard[r].containsShip(i)) { onBoard = false; }
            else { onBoard = true; break; }
        }
        
        shot = std::find(spacesFiredUpon.begin(), spacesFiredUpon.end(), i) != spacesFiredUpon.end(); //if location i is in spacesFiredUpon (aka been fired upon)
        if(onBoard && shot) { std::cout << 'x';  } //hit ship
        else if(onBoard && !shot) { //afloat ship
            if(showShips) { std::cout << 'o'; } //only print 'o' (afloat ship) if showShips is true
            else { std::cout << '='; }
        }
        else if(shot && !onBoard) { std::cout << 'n'; } //fired but no ship
        else { std::cout << '='; } //free space
        std::cout << "   ";
        
        if(i%10 == 9) { std::cout << "\n"; }
    }
    std::cout << border << "\n";
}

bool Board::rangeIsValid(int head, int tail) {
    if(head >= 0 && tail >= 0 && head < 100 && tail < 100) {
        return true;
    }
    return false;
}

Ship Board::getShipByCoord(int coord) {
    for(size_t i = 0; i < shipsOnBoard.size(); i++) {
        if(shipsOnBoard[i].containsShip(coord)) { return shipsOnBoard[i]; }
    }
    return Ship("", -1, -1);
}

bool Board::rangeIsOccupied(int head, int tail) {
    while(head != tail) {
        if(getShipByCoord(head).getName() != "") {
            return true;
        }
        
        if(head/10 == tail/10) { //if same x coord
            if(head < tail) {
                head++;
            }
            else {
                head--;
            }
        }
        else if(head%10 == tail%10) { //if same y coord
            if(head < tail) {
                head += 10;
            }
            else {
                head -= 10;
            }
        }
        else { return true; } //if coordinate overflows over multiple rows
    }
    
    if(getShipByCoord(head).getName() != "") {
        return true;
    }
    return false;
}


bool Board::isValidAttack(int attackLoc) {
    for(size_t i = 0; i < spacesFiredUpon.size(); i++) {
        if(spacesFiredUpon[i] == attackLoc) {
            std::cout << border << "\n";
            std::cout << "Already fired upon. ";
            return false;
        }
    }
    if(!rangeIsValid(attackLoc, attackLoc)) {
        std::cout << border << "\n";
        std::cout << "Invalid Range. ";
        return false;
    }
    return true;
}

bool Board::shipSunk(int shipCoord) { //checks if ship is sunk based on hits on board
    int hitCounter = 0;
    Ship shipAttacked = getShipByCoord(shipCoord);
    for(int i = 0; i < 100; i++) {
        if(getShipByCoord(i).getName() == shipAttacked.getName()) { //if space being searched is same as ship attacked
            if(std::find(spacesFiredUpon.begin(), spacesFiredUpon.end(), i) != spacesFiredUpon.end()) { //if shot
                hitCounter++;
            }
        }
    }
    return shipAttacked.getSize() == hitCounter;
}

void Board::sinkShip(int attackCoord) {
    for(int i = 0; i < 5; i++) {
        if(getShipByCoord(attackCoord).getName() == shipsOnBoard[i].getName()) {
            shipsOnBoard[i].sink();
        }
    }
}

bool Board::beenHit(int coord) {
    //return std::find(spacesFiredUpon.begin(), spacesFiredUpon.end(), coord) != spacesFiredUpon.end();
    for(size_t i = 0; i < spacesFiredUpon.size(); i++) {
        if(spacesFiredUpon[i] == coord) { return true; }
    }
    return false;
}

Board::Board(const Board &rhs) {
    shipsOnBoard.clear();
    spacesFiredUpon.clear();
    for(size_t i = 0; i < rhs.shipsOnBoard.size(); i++) {
        shipsOnBoard.push_back(rhs.shipsOnBoard[i]);
    }
    
    for(size_t k = 0; k < rhs.spacesFiredUpon.size(); k++) {
        spacesFiredUpon.push_back(rhs.spacesFiredUpon[k]);
    }
}

Board& Board::operator=(const Board &rhs) {
    if(this != &rhs) {
        shipsOnBoard.clear();
        spacesFiredUpon.clear();
        for(size_t i = 0; i < rhs.shipsOnBoard.size(); i++) {
            shipsOnBoard.push_back(rhs.shipsOnBoard[i]);
        }
        
        for(size_t k = 0; k < rhs.spacesFiredUpon.size(); k++) {
            spacesFiredUpon.push_back(rhs.spacesFiredUpon[k]);
        }
    }
    return *this;
}

int Board::getFreeVSpace(int coord) {
    int counter = -1;
    
    for(int i = 0; i < 10; i++) {
        if((!beenHit(coord + (i*10))) || ((beenHit(coord + (i*10)) && getShipByCoord(coord).getName() == getShipByCoord(coord + (i*10)).getName()))) {
            if(rangeIsValid(coord + (i*10), coord + (i*10))) { counter++; }
            else { break; }
        }
        else { break; }
    }
    
    for(int i = 0; i < 10; i++) {
        if((!beenHit(coord - (i*10))) || ((beenHit(coord - (i*10)) && getShipByCoord(coord).getName() == getShipByCoord(coord - (i*10)).getName()))) {
            if(rangeIsValid(coord - (i*10), coord - (i*10))) { counter++; }
            else { break; }
        }
        else { break; }
    }
    return counter;
}

int Board::getFreeHSpace(int coord) {
    int counter = -1;
    
    for(int i = 0; i < 10; i++) {
        if((!beenHit(coord + i)) || ((beenHit(coord + i) && getShipByCoord(coord).getName() == getShipByCoord(coord + i).getName()))) {
            if(((coord+i)%10 != 0)) { counter++; }
            else { break; }
        }
        else { break; }
    }
    
    for(int i = 0; i < 10; i++) {
        if((!beenHit(coord - i)) || ((beenHit(coord - i) && getShipByCoord(coord).getName() == getShipByCoord(coord - i).getName()))) {
            if(((coord-i)%10 != 9)) { counter++; }
            else { break; }
        }
        else { break; }
    }
    return counter;
}
