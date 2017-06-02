//
//  Game.cpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#include "Game.hpp"

void Game::start(int gamemode) {
    int difficulty = 0;
    //place ships
    if(gamemode == 1) { //if human vs cpu
        p1 = Player(1, "human");
        p2 = Player(2, "human");
        char placement = '\0';
        std::cout << border << "-------------------------------" << "\n";
        std::cout << "Player 1, would you like to manually place or randomize your fleet (r/m)?\n: ";
        while(placement != 'r' && placement != 'm') {
            std::cin >> placement;
            if(placement == 'm') {
                p1.placeShips();
            }
            else if(placement == 'r') {
                p1.randomizeFleet();
            }
        }
        
        placement = '\0';
        std::cout << border << "-------------------------------" << "\n";
        std::cout << "Player 2, would you like to manually place or randomize your fleet (r/m)?\n: ";
        while(placement != 'r' && placement != 'm') {
            std::cin >> placement;
            if(placement == 'm') {
                p2.placeShips();
            }
            else if(placement == 'r') {
                p2.randomizeFleet();
            }
        }
    }
    
    else if(gamemode == 2) { //if human vs cpu
        p1 = Player(1, "human");
        char placement = '\0';
        std::cout << border << "-------------------------------" << "\n";
        std::cout << "Player 1, would you like to manually place or randomize your fleet (r/m)?\n: ";
        while(placement != 'r' && placement != 'm') {
            std::cin >> placement;
            if(placement == 'm') {
                p1.placeShips();
            }
            else if(placement == 'r') {
                p1.randomizeFleet();
            }
        }
        std::cout << "--------------------------------------------\n";
        std::cout << "Please select a difficulty level for the CPU:\n1. Easy\n2. Intermediate\n3. Hard\n: ";
        while(difficulty < 1 || difficulty > 3) {
            std::cin >> difficulty;
            if(difficulty < 1 || difficulty > 3) { std::cout << "Try again\n: "; }
        }
        p2.setDifficulty(difficulty);
    }
    else if(gamemode == 3) { //if cpu vs cpu
        p1 = Player(1, "cpu");
        p1.randomizeFleet();
        std::cout << "--------------------------------------------\n";
        std::cout << "Please select a difficulty level for CPU 1:\n1. Easy\n2. Intermediate\n3. Hard\n: ";
        while(difficulty < 1 || difficulty > 3) {
            std::cin >> difficulty;
            if(difficulty < 1 || difficulty > 3) { std::cout << "Try again\n: "; }
        }
        p1.setDifficulty(difficulty);
        
        difficulty = 0;
        std::cout << "--------------------------------------------\n";
        std::cout << "Please select a difficulty level for CPU 2:\n1. Easy\n2. Intermediate\n3. Hard\n: ";
        while(difficulty < 1 || difficulty > 3) {
            std::cin >> difficulty;
            if(difficulty < 1 || difficulty > 3) { std::cout << "Try again\n: "; }
        }
        p2.setDifficulty(difficulty);
    }
    else { return; }
    
    //take turns attacking
    Player* currPlayer = &p1;
    Player* nextPlayer = &p2;
    int option = 2;
    std::string attackCoordStr;
    int attackCoord = 0;
    std::cout << "---------------------------";
    
    while(!currPlayer->getBoard().isAllSunk()) { //go until current player's board is empty
        std::cout << "\n";
        std::cout << "\n\nPlayer " << currPlayer->getID() << "'s turn:\n";
        std::cout << "---------------------------";
        std::cout << "\n";
        if(currPlayer->getType() == "cpu") {
            attackCoord = nextPlayer->getNextAttack(currPlayer->getDifficulty());
            currPlayer->attack(nextPlayer, attackCoord);
        }
        else {
            option = 2;
            while(option >= 1 && option <= 3) {
                std::cout << "Please select an option:\n";
                std::cout << border << "\n";
                std::cout << "1. Print Your Board\n2. Print Shots Already Fired\n3. Attack enemy\n";
                std::cout << border << "\n: ";
                std::cin >> option;
                switch(option) {
                    case 1:
                        currPlayer->getBoard().print(true); //prints myBoard
                        break;
                    case 2:
                        nextPlayer->getBoard().print(false); //prints enemy's board without ships
                        break;
                    case 3:
                        nextPlayer->getBoard().print(false);
                        std::cout << "Please enter a coordinate to attack (a3)\n: ";
                        std::cin >> attackCoordStr;
                        
                        if(attackCoordStr[0] >= 'A' && attackCoordStr[0] <= 'Z') {
                            attackCoord = attackCoordStr[0] - 'A';
                        }
                        else if(attackCoordStr[0] >= 'a' && attackCoordStr[0] <= 'z') {
                            attackCoord = attackCoordStr[0] - 'a';
                        }
                        attackCoord = attackCoord + (10*(attackCoordStr[1] - '0'));
                        
                        if(nextPlayer->getBoard().isValidAttack(attackCoord) && attackCoordStr.size() == 2) {
                            std::cout << "------------------------------------\n";
                            currPlayer->attack(nextPlayer, attackCoord);
                            //exit loop after attack
                            option = -1;
                        }
                        else {
                            //reset option if invalid target
                            std::cout << "Please try again.\n";
                            std::cout << border << "\n";
                            option = 2;
                        }
                        break;
                    default:
                        std::cout << border << "\n";
                        std::cout << "Invalid option, please try again.\n";
                        std::cout << border << "\n";
                        option = 2; //reset option so player can try again
                        break;
                }
            }
        }
        std::swap(currPlayer, nextPlayer);
        numOfTurns++;
    }
    std::cout << "\n\nPlayer " << nextPlayer->getID() << " WON!\nCONGRATULATIONS!!!\nNumber Of Turns = " << numOfTurns/2 << "\n";
}
