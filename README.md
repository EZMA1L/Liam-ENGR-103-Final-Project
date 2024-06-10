# Liam-ENGR-103-Final-Project
# Repo I made for ENGR 103, specifically my final project
---
# All the code is my own except for the voicebox code for the speaker from the Talk_US_TI99 example Arduino project.
---
## Basic Layout of this project & Descriptions I will be providing w/ example code:
1. What the project is, rules, specs, guidelines, inputs and outputs
2. Pre-Setup
3. Setup
4. Loop
5. Loading Zone (Loop funct 1)
6. Gameplay (Loop funct 2)
7. Standby Mode (Loop funct 3)
8. Error Mode (Loop funct 4)
9. Interrupts
10. Lighting Pattern function
11. User Input function
12. Level Win function
13. Game Win function
14. Error function

## This is a pretty big project, but I tried to split it up into distinct groupings to make it easier (for me) to process, debug, and modify.
---
# What is this project?
> This is a 9 level game where you, the player, interface with a CircuitPlayground Express board. The board will turn on the neopixels on the left side of the board or the right side of the board, and it is up to you to memorize the side and in which order the neopixels turn on. To help with this, the left side neopixels will be lit up blue and the right side red, and each will make a different tone. If you input the same pattern the board shows you by pressing either the left or right button, you win, and move onto the next level. If you don't press the right button or within 4 seconds, you will fail the game and be sent back to level 1.

![Neopixels](https://cdn-learn.adafruit.com/assets/assets/000/034/012/large1024/circuit_playground_neoorder.jpg)
---
## Specifications/Inputs/Outputs:
On the CircuitPlayground Express board with a usb cable:

	| Itemization	 | Task (Input/Output) | 
 	| -------------- | ------------------- | 
	| Neopixels 0-9  |       Output        |
	| Left Button    | 	 Input         |
	| Right Button   |	 Input         |
 	| Switch 	 |	 Input         |
  Using Arduino IDE 2.3.2
---
## References
> 4 references are used. Circuitplayground to refer to circuitplayground libraries, asyncdelay to use asyncdelay libraries and functions, and Wire & SPI to use the speaker voice functions.
---
# Pre-Setup
### In pre-setup, a lot of variables are declared. They are largely split up into their seperate variable types

`long rand_Number = 0;  // used to set a random value to determine left or right led pattern in game_Lights_Level
int rand_Int = 0;      // can't use ints for rand() so need to set this value to use in int arrays
`
`
bool game_On = 0;        // variable used to turn on and off the waiting zone between levels
bool game_Win = 0;       // variable used to determine whether or not player won the game
bool left_Pressed = 0;   // used to break out of large for loop in user input program
bool right_Pressed = 0;  // used to break out of large for loop in user input program
bool clear_Pixels = 0;   // used to turn off all neopixels once when switching back to game from standby mode
`
`
int level_Win = 0;              // used to determine whether the player won the level or gets sent back to level 1
int game_Level = 0;             // used to tell the user & program what level of the game they are on
int game_Level_Save = 0;        // used by Mode 1, also known as error code 1, where user interrupts game while it is displaying pattern to play
int game_Difficulty = 2;        // used to tell the light pattern code and user input code how many times to display lights and how many times to check for input
int game_Difficulty_Input = 0;  // used in user input section to be able to skip the rest of light pattern showing if correct input already played
int light_Pattern_Stage = 0;    // used by game and user input arrays to input game and user left/right side (1 or 2) integer values into corresponding array slot
int user_Matched_Pattern = 0;   // used in user input section to set an int value for the number of left and right inputs that match game_Matched_Pattern
int game_Matched_Pattern = 0;   // used in user input section to set a stacking int value (1 for left, 2 for right) for every pattern in array game_Pattern_Int
`
`
int left_Leds[] = { 0, 1, 2, 3, 4 };                   // array for various lighting patterns utilizing the left side neopixels of the CircuitPlayground
int right_Leds[] = { 5, 6, 7, 8, 9 };                  // array for various lighting patterns utilizing the right side neopixels of the CircuitPlayground
int leds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };         // array used for various setting of all neopixels on/to a certain color within code
int ledsoffset[] = { 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 };   // array used for standby mode loading icon leading edge turning on of LED
int ledstopdown[] = { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 };  // array used for standby mode loading icon trailing edge turning off of LED
int user_Pattern_Int[11];                              // array used for storing the user left/right pattern of inputs (LB = 1 = left, RB = 2 = right)
int game_Pattern_Int[11];                              // array used for storing the game left/right pattern (1 = left, 2 = right)
String game_Pattern[11];                               // array used for storing the game left/right pattern (left or right) to display for the user
String pattern_Side = "nothing";                       // used for String game_Pattern array naming
`
`
const int interruptPinLB = 4;      // left button interrupt pin
const int interruptPinRB = 5;      // right button interrupt pin
const int interruptPinSwitch = 7;  // switch interrupt pin
`
`
volatile bool leftButton_intFlag = 0;   // flag for left button pressed
volatile bool rightButton_intFlag = 0;  // flag for right button pressed
volatile bool switch_intFlag = 0;       // flag for switch pressed
`
`
AsyncDelay delay_4s;  // 4 econd delay for user input section, will fail the user if no input detected within timeframe of 4000 ms.
`

## Setup

## A bit about myself:
I like cats
