//
//  Player.cpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#include "Player.hpp"
#include <chrono>
#include <thread>

const char alphabet[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

Player& Player::operator=(const Player &rhs) {
    if(this != &rhs) {
        id = rhs.id;
        type = rhs.type;
        myBoard = rhs.myBoard;
    }
    return *this;
}

Player::Player(const Player &rhs) {
    id = rhs.id;
    type = rhs.type;
    myBoard = rhs.myBoard;
}

void Player::placeShips() {
    std::vector<Ship> Ships = {Ship("Carrier", 10, 14), Ship("Battleship", 10, 13), Ship("Cruiser", 10, 12), Ship("Submarine", 10, 12), Ship("Destroyer", 10, 11) };
    
    int shipNumber, shipHead, shipTail;
    for(int i = 0; i < 5; i++) {
        std::cout << "---------------------------";
        std::cout << "\nRemaining Ships:\n";
        for(size_t k = 0; k < Ships.size(); k++) {
            if(!Ships[k].isSunk()) { std::cout << k << ". " << Ships[k].getName() << " - " << Ships[k].getSize() << "\n"; }
        }
        std::cout << border << "\n";
        std::cout << "Please select a ship to place (0-4)\n: ";
        std::cin >> shipNumber;
        std::cout << border << "\n";
        std::cout << "Please enter location of the ship's head\n: ";
        std::cin >> shipHead;
        std::cout << border << "\n";
        std::cout << "Please enter location of the ship's tail\n: ";
        std::cin >> shipTail;
        std::cout << border << "\n";
        if(myBoard.rangeIsValid(shipHead, shipTail)) { // if range is unoccupied and within board limits
            myBoard.addShip(Ship(Ships[shipNumber].getName(), shipHead, shipTail));
            Ships[shipNumber].sink();
        }
        else {
            std::cout << "Invalid placement, please try again\n";
            i--;
        }
    }
}

void Player::randomizeFleet() {
    std::vector<Ship> Ships = {Ship("Carrier", 10, 14), Ship("Battleship", 10, 13), Ship("Cruiser", 10, 12), Ship("Submarine", 10, 12), Ship("Destroyer", 10, 11) };
    
    for(int i = 0; i < 5; i++) {
        int startX = rand() % 10;
        int startY = rand() % 10;
        int endX = startX;
        int endY = startY;
        
        //go vert
        if(rand() % 2 == 0) {
            //go up
            if(rand() % 2 == 0) {
                endX -= (Ships[i].getSize() - 1);
            }
            //go down
            else {
                endX += (Ships[i].getSize() - 1);
            }
        }
        //go horiz
        else {
            //go left
            if(rand() % 2 == 0) {
                endY -= (Ships[i].getSize() - 1);
            }
            //go right
            else {
                endY += (Ships[i].getSize() - 1);
            }
        }
        
        int head = startY*10 + startX;
        int tail = endY*10 + endX;
        if(myBoard.rangeIsValid(head, tail) && !myBoard.rangeIsOccupied(head, tail)) {
            myBoard.addShip(Ship(Ships[i].getName(), head, tail)); //i is ship number
        }
        else {
            i--;
        }
    }
}

//returns player board
Board Player::getBoard() {
    return myBoard;
}


void Player::attack(Player* enemy, int attackCoord) {
    Ship spaceBeingAttacked = enemy->myBoard.getShipByCoord(attackCoord);
    enemy->myBoard.fire(attackCoord); //add shot to enemies myBoard
    std::cout << "Attacking: " << alphabet[attackCoord%10] << attackCoord/10 << "\n";
    
    if(spaceBeingAttacked.getName() != "") { //if hit
        std::cout << "HIT! " << spaceBeingAttacked.getName() << " ship hit!\n";
        if(enemy->myBoard.shipSunk(attackCoord)) { //if sunk
            std::cout << "SUNK! " << spaceBeingAttacked.getName() << " ship sunk!\n";
            enemy->myBoard.sinkShip(attackCoord);
        }
    }
    else {
        std::cout << "MISS!\n";
    }
    std::cout << "---------------------------";
}

int Player::getNextAttack(int difficulty) { //if diffculty is not 1 or 2, difficulty = hard
    int probBoard[100];
    
    //clear prob board
    for(int i = 0; i < 100; i++) {
        probBoard[i] = 0;
    }
    
    //reset largest ship
    int largestShip = 0;
    
    //assign largest ship
    for(int i = 0; i < 100; i++) {
        Ship currShip = myBoard.getShipByCoord(i);
        if(!currShip.isSunk()) { //if ship is still afloat
            if(currShip.getSize() > largestShip) { largestShip = currShip.getSize(); } //reassign largest ship on board
        }
    }
    
    std::vector<int> allPossible;
    if(difficulty != 2) { //calculate base prob only for 'hard' and 'easy' difficulty
        //assign base prob
        //for all horizontal coordinates
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < (10 - largestShip +1); j++) {
                for(int k = 0; k < (largestShip); k++) {
                    if(!myBoard.beenHit((i*10) + j + k) || (myBoard.beenHit((i*10) + j + k) && !myBoard.getShipByCoord((i*10) + j + k).isSunk())) { //if not hit or if hit but contains a ship that is not sunk
                        allPossible.push_back((i*10) + j + k);
                    }
                    else {
                        for(int m = 0; m < k; m++) {
                            allPossible.pop_back();
                        }
                        break;
                    }
                }
                //for all vertical coordinates
                for(int z = 0; z < (largestShip); z++) {
                    if(!myBoard.beenHit(((j+z)*10) + i)) {
                        allPossible.push_back(((j+z)*10) + i);
                    }
                    else {
                        for(int m = 0; m < z; m++) {
                            allPossible.pop_back();
                        }
                        break;
                    }
                }
            }
        }
    }
    
    //update probability board based on the coordinates possible for the largest ship to occupy
    for(int p = 0; p < allPossible.size(); p++) {
        probBoard[allPossible[p]] += 1;
    }
    
    //add improvements based on hits
    if(difficulty != 1) { //update based on hits if difficulty is not 'easy'
        for(int i = 0; i < 10; i++) {
            for(int k = 0; k < 10; k++) {
                int currCoord = (i*10) + k;
                int leftCoord = (i*10) + k-1;
                int rightCoord = (i*10) + k+1;
                int upCoord = ((i-1)*10) + k;
                int downCoord = ((i+1)*10) + k;
                if(myBoard.beenHit(currCoord) && (myBoard.getShipByCoord(currCoord).getName() != "") && !myBoard.getShipByCoord(currCoord).isSunk()) { //currCoord is a coordinate that has been hit, contains a ship and is not sunk
                    if((myBoard.beenHit(leftCoord) || myBoard.beenHit(rightCoord)) && (myBoard.getShipByCoord(leftCoord) == myBoard.getShipByCoord(currCoord) || myBoard.getShipByCoord(rightCoord) == myBoard.getShipByCoord(currCoord)) && difficulty != 2) { //if space to left or right is hit and the same ship and not sunk and difficulty is not 2
                        //increment only the left and right
                        if(!myBoard.getShipByCoord(currCoord).isSunk()) { //ship cannot be sunk as well
                            if(myBoard.getFreeHSpace(currCoord) >= myBoard.getShipByCoord(currCoord).getSize()) { //ensure there is enough free space for the ship to fit if placed on either of these spaces
                                if(myBoard.rangeIsValid(leftCoord, leftCoord)) { probBoard[leftCoord] += 25; }
                                if(myBoard.rangeIsValid(rightCoord, rightCoord)) { probBoard[rightCoord] += 25; }
                            }
                        }
                    }
                    
                    else if((myBoard.beenHit(upCoord) || myBoard.beenHit(downCoord)) && (myBoard.getShipByCoord(upCoord) == myBoard.getShipByCoord(currCoord) || myBoard.getShipByCoord(downCoord) == myBoard.getShipByCoord(currCoord)) && difficulty != 2) { //if space on top or bottom is hit and the same ship and not sunk and difficulty is not 2
                        //increment only the top and bottom
                        if(!myBoard.getShipByCoord(currCoord).isSunk()) { //ship cannot be sunk as well
                            if(myBoard.getFreeVSpace(currCoord) >= myBoard.getShipByCoord(currCoord).getSize()) {
                                if(myBoard.rangeIsValid(upCoord, upCoord)) { probBoard[upCoord] += 25; }
                                if(myBoard.rangeIsValid(downCoord, downCoord)) { probBoard[downCoord] += 25; }
                            }
                        }
                    }
                    
                    //increment all directions by 20 if only one space of a ship has been hit
                    else {
                        if(myBoard.getFreeVSpace(currCoord) >= myBoard.getShipByCoord(currCoord).getSize()) {
                            if(myBoard.rangeIsValid(upCoord, upCoord)) { probBoard[upCoord] += 20; }
                            if(myBoard.rangeIsValid(downCoord, downCoord)) { probBoard[downCoord] += 20; }
                        }
                        if(myBoard.getFreeHSpace(currCoord) >= myBoard.getShipByCoord(currCoord).getSize()) {
                            if(myBoard.rangeIsValid(leftCoord, leftCoord)) { probBoard[leftCoord] += 20; }
                            if(myBoard.rangeIsValid(rightCoord, rightCoord)) { probBoard[rightCoord] += 20; }
                        }
                    }
                }
            }
        }
    }
    
    //marks odds at 0 if already fired upon
    for(int n = 0; n < 100; n++) {
        if(myBoard.beenHit(n)) {
            probBoard[n] = 0;
        }
    }
    
    //find next best attack coordinate based on prob board
    int highestValue = 0;
    std::vector<int> highestSpaces;
    for(int j = 0; j < 100; j++) { //finds the highest space on probBoard
        if(probBoard[j] > highestValue) { highestValue = probBoard[j]; }
    }
    for(int r = 0; r < 100; r++) { //adds all equal highest probablity coordinates to highestSpaces
        if(probBoard[r] == highestValue) {
            highestSpaces.push_back(r);
        }
    }
    //selects a random highest space if there are multiple that are equal
    int randNum = rand() % highestSpaces.size();
    return highestSpaces[randNum];
}
