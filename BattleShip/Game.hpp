//
//  Game.hpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"

class Game {
private:
    Player p1;
    Player p2;
    int numOfTurns = 0;
public:
    Game() { p2 = Player(2, "cpu"); p2.randomizeFleet(); }
    void start(int gamemode); //starts the game
    int getNumOfTurns() { return numOfTurns; }
};

#endif /* Game_hpp */
