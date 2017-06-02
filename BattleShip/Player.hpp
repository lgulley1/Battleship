//
//  Player.hpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Board.hpp"
#include <stdio.h>
#include <time.h>

class Player {
private:
    int id = -1;
    std::string type = "";
    Board myBoard;
    int difficulty = 3;
public:
    Player() {}
    Player(int nID, std::string nType) { id = nID; type = nType; }
    Player(int nID, std::string nType, int nDifficulty) { id = nID; type = nType; difficulty = nDifficulty; }
    Player(const Player &rhs);
    Player& operator=(const Player &rhs);
    std::string getType() { return type; }
    void setDifficulty(int nDiff) { difficulty = nDiff; }
    int getDifficulty() { return difficulty; }
    void placeShips(); //for human player to place ships
    void randomizeFleet(); //randomly places ships
    void attack(Player*, int); //attacks a coordinate on the enemy player's board
    Board getBoard();
    int getID() { return id; }
    int getNextAttack(int); //calculates best coordinate to attack next based on difficulty level
};

#endif /* Player_hpp */
