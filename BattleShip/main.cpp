//
//  main.cpp
//  BattleShip
//
//  Created by Luke Gulley on 6/2/17.
//  Copyright © 2017 Luke Gulley. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int gamemode = 0;
    char playAgain = '\0';
    Game* newGame;
    while(gamemode == 0) {
        std::cout << "BATTLESHIP - GAME STARTED:\n";
        std::cout << "-------------------------------\n";
        std::cout << "Please select a gamemode:\n";
        std::cout << "1. Human vs. Human\n2. Human vs. CPU\n3. CPU vs. CPU\n4. Quit\n: ";
        std::cin >> gamemode;
        if(gamemode > 0 && gamemode < 5) {
            if(gamemode == 4) { break; }
            newGame = new Game;
            newGame->start(gamemode); //start game
            delete newGame;
            
            std::cout << "Play again (y/n)?\n: ";
            std::cin >> playAgain;
            
            while(playAgain != 'y' && playAgain != 'n') {
                std::cout << "---------------------------\n";
                std::cout << "Invalid option, try again.\n";
                std::cout << "---------------------------" << "\n";
                std::cout << "Play again (y/n)?\n: ";
                std::cin >> playAgain;
            }
            
            if(playAgain == 'y') { std::cout << "\n"; gamemode = 0; }
            else if(playAgain == 'n') { gamemode = -1; }
        }
        else {
            std::cout << "-------------------------------\n" << "Please try again.\n" << border << "\n";
            gamemode = 0;
        }
    }
    std::cout << "---------------------------\n";
    std::cout << "Thanks for playing!\n";
    return 0;
}
