### Liam Edwards Final Project Documentation
June 6th Update
## What is the game?

There are 2 sides to the game, left and right, neopixels on the left side of the board light up blue and neopixels on the right side of the board light up red. 
Game will await a user input from both buttons to start first level. For 1st level, user will be shown a random pattern of 4 either left or right side lights on
(ex. [L, L, R, L]) and after being shown the whole pattern user will be asked to repeat the pattern back in sequence within a time limit. 
If pattern is repeated back using the left and right buttons in the right sequence, the game will display your reward. The game will wait for user input in the form
of pressing both buttons to start the next level if they choose, and the next level will be a similar setup but with 1 more pattern step added (4 -> 5 from level 1 to level 2).
Switch can also be turned off to be board in a standby mode, score will be saved in this state.

## Inputs and Outputs
1. Neopixels: Display light patterns, output
2. left button: detect user input for left light pattern matching, input
3. right button: detect user input for right light pattern matching, input
4. switch: detect user input for game on/off, input
5. game_Level: main variable used to increase the difficulty of the game, input
6. Speaker: plays audio when user wins the level, output
    
