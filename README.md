# Battleship
<b>A simple battleship game written in c++.</b>

<i>Runs in the terminal.</i>

There are 3 different game modes.
1. Human vs. Human
2. Human vs. CPU
3. CPU vs. CPU
  
There are also 3 different difficulty settings when playing against a CPU player.
  1. Easy Mode
    - CPU guesses randomly
  2. Intermediate Mode
    - CPU guess randomly until a ship is hit
    - For every ship hit, the 4 immediate spaces surrounding the space are given higher priority for the next attack
    - Finally it guesses the square with the greatest probability.
  3. Hard mode
    - CPU detects the largest unsunk ship.
    - It then determines how many times the largest ship can be placed on each space, given it's inability to cross a border         or a space already hit (this serves as a base probability)
    - For every ship hit, the 4 immediate spaces surrounding the space are given higher priority for the next attack
      - If a ship has been hit more than once, only the spaces surrounding that corresponding direction will be updated
    - It also detects if there is enough free space horizontally or vertically for the remainder of the ship to fit
      - If it cannot fit, the corresponding spaces are not updated

A test of 10,000 games was conducted. The following is the average number of turns per game, given each difficulty.
1. Easy - 96.63
2. Intermediate - 70.88
3. Hard - 45.72
