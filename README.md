# Battleship
A simple battleship game written in c++.

There are 3 different game modes.
1. Human vs. Human
2. Human vs. CPU
3. CPU vs. CPU
  
There are also 3 different difficulty settings when playing against a CPU player.
  1. Easy Mode
    - CPU guesses randomly
  2. Intermediate Mode
    - CPU detects the largest unsunk ship.
    - It then determines how many ways it can fit on a specific space of the board, based on the board's border and already attacked spaces.
    - Finally it guesses the square with the greatest probability.
  3. Hard mode
    - CPU inherits the method from intermediate mode as a base probability
    - CPU updates the surrounding spaces of a hit ship that isn't already sunk, marking them with a greater probability
    - It also detects if there is enough free space horizontally or vertically for the remainder of the ship to fit
      - If it cannot fit, the corresponding spaces are not updated
