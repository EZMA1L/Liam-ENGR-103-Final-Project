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
### In pre-setup, a lot of variables are declared. They are largely split up into their seperate variable types and have been neatly identified in-line so I will just copy my code here
```

int Mode = 0;  // user input/game error codes:
/*
*  Error Code 1; user presses button while game displaying pattern.
*              pattern will repeat after showing it is unhappy
*  Mode 2: user didn't press button fast enough
*             will restart at level 1
*/

long rand_Number = 0;  // used to set a random value to determine left or right led pattern in game_Lights_Level
int rand_Int = 0;      // can't use ints for rand() so need to set this value to use in int arrays

bool game_On = 0;        // variable used to turn on and off the waiting zone between levels
bool game_Win = 0;       // variable used to determine whether or not player won the game
bool left_Pressed = 0;   // used to break out of large for loop in user input program
bool right_Pressed = 0;  // used to break out of large for loop in user input program
bool clear_Pixels = 0;   // used to turn off all neopixels once when switching back to game from standby mode

int level_Win = 0;              // used to determine whether the player won the level or gets sent back to level 1
int game_Level = 0;             // used to tell the user & program what level of the game they are on
int game_Level_Save = 0;        // used by Mode 1, also known as error code 1, where user interrupts game while it is displaying pattern to play
int game_Difficulty = 2;        // used to tell the light pattern code and user input code how many times to display lights and how many times to check for input
int game_Difficulty_Input = 0;  // used in user input section to be able to skip the rest of light pattern showing if correct input already played
int light_Pattern_Stage = 0;    // used by game and user input arrays to input game and user left/right side (1 or 2) integer values into corresponding array slot
int user_Matched_Pattern = 0;   // used in user input section to set an int value for the number of left and right inputs that match game_Matched_Pattern
int game_Matched_Pattern = 0;   // used in user input section to set a stacking int value (1 for left, 2 for right) for every pattern in array game_Pattern_Int

int left_Leds[] = { 0, 1, 2, 3, 4 };                   // array for various lighting patterns utilizing the left side neopixels of the CircuitPlayground
int right_Leds[] = { 5, 6, 7, 8, 9 };                  // array for various lighting patterns utilizing the right side neopixels of the CircuitPlayground
int leds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };         // array used for various setting of all neopixels on/to a certain color within code
int ledsoffset[] = { 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 };   // array used for standby mode loading icon leading edge turning on of LED
int ledstopdown[] = { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 };  // array used for standby mode loading icon trailing edge turning off of LED
int user_Pattern_Int[11];                              // array used for storing the user left/right pattern of inputs (LB = 1 = left, RB = 2 = right)
int game_Pattern_Int[11];                              // array used for storing the game left/right pattern (1 = left, 2 = right)
String game_Pattern[11];                               // array used for storing the game left/right pattern (left or right) to display for the user
String pattern_Side = "nothing";                       // used for String game_Pattern array naming

const int interruptPinLB = 4;      // left button interrupt pin
const int interruptPinRB = 5;      // right button interrupt pin
const int interruptPinSwitch = 7;  // switch interrupt pin

volatile bool leftButton_intFlag = 0;   // flag for left button pressed
volatile bool rightButton_intFlag = 0;  // flag for right button pressed
volatile bool switch_intFlag = 0;       // flag for switch pressed

AsyncDelay delay_4s;  // 4 econd delay for user input section, will fail the user if no input detected within timeframe of 4000 ms.

```
--- 
## Setup
In setup, a few basic steps happen:
- sensors are initialized
- serial monitor is initialized
- buttons and switch interrupt functions are stated
- start-up animation is performed
- switch state is read

```
Serial.begin(9600);
  CircuitPlayground.begin();
  delay(500);
  Serial.println("Booting Up");
  delay(500);
  randomSeed(analogRead(0));
  CircuitPlayground.clearPixels();
  attachInterrupt(digitalPinToInterrupt(interruptPinRB), rightButtonISR, FALLING);  // check right button, if pressed run through rightButtonISR code once
  attachInterrupt(digitalPinToInterrupt(interruptPinLB), leftButtonISR, FALLING);   // check left button, if pressed run through rightButtonISR code once
  attachInterrupt(digitalPinToInterrupt(interruptPinSwitch), switchISR, CHANGE);    // check if switch has been moved, run through switchISR code once
  Serial.println("Game starting soon");
  delay(500);
  Serial.println("Loading: 0%");
  delay(400);
  CircuitPlayground.setPixelColor(0, 0, 255, 0);
  CircuitPlayground.setPixelColor(1, 0, 255, 0);
  Serial.println("Loading 25%");
  delay(500);
  CircuitPlayground.setPixelColor(3, 0, 255, 0);
  CircuitPlayground.setPixelColor(4, 0, 255, 0);
  Serial.println("Loading 50%");
  delay(500);
  CircuitPlayground.setPixelColor(5, 0, 255, 0);
  CircuitPlayground.setPixelColor(6, 0, 255, 0);
  Serial.println("Loading 75%");
  delay(500);
  CircuitPlayground.setPixelColor(8, 0, 255, 0);
  CircuitPlayground.setPixelColor(9, 0, 255, 0);
  Serial.println("Loading 100%");
  delay(400);
  for (int a = 0; a < 4; a++) {
    CircuitPlayground.clearPixels();
    for (int i = 0; i <= 9; i++) {
      CircuitPlayground.setPixelColor(leds[i], random(0, 80), random(40, 200), random(25, 190));
      delay(50);
    }
    CircuitPlayground.playTone(880, 50);
  }
  delay(400);
  Serial.println("Game ready");
  switch_intFlag = digitalRead(7);  // check switch state at startup
  CircuitPlayground.clearPixels();
  CircuitPlayground.speaker.say(spREADY_TO_START);
```
--- 
# Loop
## Here I will start out with all the code and then split it up into its pieces to explain what is going on
```
void loop() {
  // game only runs when switch is turned on
  if (switch_intFlag) {
    // if statement for switching back to game from standby mode
    if (clear_Pixels) {
      CircuitPlayground.clearPixels();
      Serial.println("Game back on. In Loading Zone. Good luck!");
      clear_Pixels = 0;
    }
    // loading zone function that will loop between game levels. Shows to the player clearly what buttons to press to continue with flashing green lights
    if (!game_Win) {
      delay(40);
      CircuitPlayground.setPixelColor(2, 0, 255, 0);
      CircuitPlayground.setPixelColor(7, 0, 255, 0);
      for (int i = 100; i > 0; i--) {
        CircuitPlayground.setPixelColor(1, 0, i, 0);
        CircuitPlayground.setPixelColor(3, 0, i, 0);
        CircuitPlayground.setPixelColor(6, 0, i, 0);
        CircuitPlayground.setPixelColor(8, 0, i, 0);
        if (leftButton_intFlag || rightButton_intFlag) {
          break;
        }
        delay(2);
      }
    }

    if (leftButton_intFlag || rightButton_intFlag && !game_On) {
      // loading zone between game levels
      switch (game_Level) {
        case 0:  // level 1 loading zone to gameplay, sets game_On to true
          delay(50);
          Serial.println("Level 1 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 1;
          game_On = 1;
          break;
        case 1:  // unused
          break;
        case 2:  // level 2 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 2 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 2;
          game_On = 1;
          break;
        case 3:  // level 3 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 3 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 3;
          game_On = 1;
          break;
        case 4:  // level 4 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 4 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 4;
          game_On = 1;
          break;
        case 5:  // level 5 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 5 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 5;
          game_On = 1;
          break;
        case 6:  // level 6 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 6 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 6;
          game_On = 1;
          break;
        case 7:  // level 7 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 7 Starting");
          Serial.println("TWO more levels to go");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 7;
          game_On = 1;
          break;
        case 8:  // level 8 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 8 Starting");
          Serial.println("Only ONE more level to go!");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 8;
          game_On = 1;
          break;
        case 9:  // level 9 loading zone to gameplay, see case 0
          delay(50);
          Serial.println("Level 9 Starting");
          Serial.println("This is the final level!");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 9;
          game_On = 1;
          break;
        case 10:  // game win condition met, go to game_On and play game win function
          delay(50);
          game_Level = 10;
          game_On = 1;
          game_Win = 1;
          break;
      }
    }
    // displays when the left button has been pressed, plays a tone
    if (leftButton_intFlag) {
      Serial.println("Left Button pressed!");
      CircuitPlayground.playTone(523.25, 40);
      CircuitPlayground.setPixelColor(2, 0, 0, 255);
      CircuitPlayground.setPixelColor(1, 0, 0, 255);
      CircuitPlayground.setPixelColor(3, 0, 0, 255);
      delay(10);
      CircuitPlayground.setPixelColor(0, 0, 0, 155);
      CircuitPlayground.setPixelColor(4, 0, 0, 155);
      delay(80);
      CircuitPlayground.clearPixels();
      leftButton_intFlag = false;
    }
    // displays when the right button has been pressed, plays a tone
    if (rightButton_intFlag) {
      Serial.println("Right Button pressed!");
      CircuitPlayground.playTone(622.25, 40);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      delay(10);
      CircuitPlayground.setPixelColor(9, 155, 0, 0);
      CircuitPlayground.setPixelColor(5, 155, 0, 0);
      delay(80);
      CircuitPlayground.clearPixels();
      CircuitPlayground.clearPixels();
      rightButton_intFlag = false;
    }
    /* level 1 code: 1 light left or right, user inputs same pattern to win
    *  each level incriments the number of light patterns and thus inputs required to pass the level by 1.
    */
    if (game_On) {
      switch (game_Level) {
        case 1:  // level 1, light pattern then user input section, check if input = game pattern, if so increase game_Level by 1
          CircuitPlayground.speaker.say(spONE);
          game_Difficulty = 1;
          game_Lights_Level();  // plays light pattern 4 times
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();  // checks for 4 inputs from the user
          if (level_Win == 1) {
            Serial.println("USER BEAT THE LEVEL");
            game_Lights_Level_Won();  // plays won level happy light sequence and bumps up difficulty by 1
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 1");
          CircuitPlayground.setPixelColor(2, 255, 255, 255);
          break;
        case 2:  // level 2, see level 1
          CircuitPlayground.speaker.say(spTWO);
          game_Difficulty = 2;
          Serial.println("Level 2 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 2nd LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 2");
          break;
        case 3:  // level 3, see level 1
          CircuitPlayground.speaker.say(spTHREE);
          game_Difficulty = 3;
          Serial.println("Level 3 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 3rd LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 3");
          break;
        case 4:  // level 4, see level 1
          CircuitPlayground.speaker.say(spFOUR);
          game_Difficulty = 4;
          Serial.println("Level 4 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 4th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 4");
          break;
        case 5:  // level 5, see level 1
          CircuitPlayground.speaker.say(spFIVE);
          game_Difficulty = 5;
          Serial.println("Level 5 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 5th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 5");
          break;
        case 6:  // level 6, see level 1
          CircuitPlayground.speaker.say(spSIX);
          game_Difficulty = 6;
          Serial.println("Level 6 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 6th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 6");
          break;
        case 7:  // level 7, see level 1
          CircuitPlayground.speaker.say(spSEVEN);
          game_Difficulty = 7;
          Serial.println("Level 7 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 7th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 7");
          break;
        case 8:  // level 8, see level 1
          CircuitPlayground.speaker.say(spEIGHT);
          game_Difficulty = 8;
          Serial.println("Level 8 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 8th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 8");
          break;
        case 9:  // level 9, see level 1
          CircuitPlayground.speaker.say(spNINE);
          game_Difficulty = 9;
          Serial.println("Level 9 Start");
          game_Lights_Level();
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();
          if (level_Win == 1) {
            Serial.println("USER BEAT THE 9th LEVEL");
            game_Lights_Level_Won();
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 9");
          break;
        case 10:  // placeholder to let program move on to game_Win program
          break;
      }
      if (game_Win) {
        CircuitPlayground.speaker.say(spYOU_WIN);
        game_Win_Lights();
      }
      // error codes and failure statements. The only one that matters for this game is case 2, which occurs when player pattern doesn't match game pattern
      switch (Mode) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          CircuitPlayground.speaker.say(spTRY_AGAIN);
          Mode_2_Unhappy_Pattern_Restart();
          break;
      }
    }
  }  // end of main game code
  // standby mode, shows a loading icon and you can press either button for game stats
  if (!switch_intFlag) {
    clear_Pixels = 1;
    for (int i = 0; i <= 9; i++) {
      CircuitPlayground.setPixelColor(leds[i], 150, 0, 100);
      delay(50);
      CircuitPlayground.setPixelColor(ledsoffset[i], 0, 0, 0);
      delay(30);
      if (switch_intFlag || leftButton_intFlag || rightButton_intFlag) {
        break;
      }
    }
    if (leftButton_intFlag) {
      Serial.println("Left Button pressed!");
      CircuitPlayground.playTone(523.25, 40);
      CircuitPlayground.setPixelColor(2, 0, 0, 255);
      CircuitPlayground.setPixelColor(1, 0, 0, 255);
      CircuitPlayground.setPixelColor(3, 0, 0, 255);
      delay(10);
      CircuitPlayground.setPixelColor(0, 0, 0, 155);
      CircuitPlayground.setPixelColor(4, 0, 0, 155);
      delay(80);
      CircuitPlayground.clearPixels();
      Serial.println("Game off. In Standby Mode.");
      Serial.print("User Level is currently at: ");
      Serial.print(game_Level);
      Serial.print("\n"
                   "Max Level is 9. You are ");
      Serial.print(9 - game_Level);
      Serial.print(" Levels away from finishing the game. You've got this!");
      leftButton_intFlag = false;
    }

    if (rightButton_intFlag) {
      Serial.println("Right Button pressed!");
      CircuitPlayground.playTone(622.25, 40);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      delay(10);
      CircuitPlayground.setPixelColor(9, 155, 0, 0);
      CircuitPlayground.setPixelColor(5, 155, 0, 0);
      delay(80);
      CircuitPlayground.clearPixels();
      CircuitPlayground.clearPixels();
      Serial.println("Game off. In Standby Mode.");
      Serial.print("User Level is currently at: ");
      Serial.print(game_Level);
      Serial.print("\n"
                   "Max Level is 10. You are ");
      Serial.print(10 - game_Level);
      Serial.print(" Levels away from finishing the game. You've got this!");
      rightButton_intFlag = false;
    }
  }
}  // end of standby mode code
```

all of the if (leftButton_intFlag) & if (rightButton_intFlag) statemenets are mostly to display to the user some feedback when they press a button, so the left button for example will display blue on all of the neopixels on the left side of the board, starting from the one closest to the button and then radiating outwards.

Loading Zone code is setup to flash green near the left and right buttons, and once either the left or right button is pressed the game moves on to the gameplay function corresponding to the current game_Level value

Gameplay code follows this setup for levels 1-9;
```
 if (game_On) {
      switch (game_Level) {
        case 1:  // level 1, light pattern then user input section, check if input = game pattern, if so increase game_Level by 1
          CircuitPlayground.speaker.say(spONE);
          game_Difficulty = 1;
          game_Lights_Level();  // plays light pattern 4 times
          CircuitPlayground.clearPixels();
          delay(500);
          delay_4s.start(4000, AsyncDelay::MILLIS);
          game_User_Input_Level();  // checks for 4 inputs from the user
          if (level_Win == 1) {
            Serial.println("USER BEAT THE LEVEL");
            game_Lights_Level_Won();  // plays won level happy light sequence and bumps up difficulty by 1
          } else {
            Mode = 2;
          }
          for (int i = 0; i <= game_Difficulty; i++) {
            user_Pattern_Int[i] = 0;
          }
          Serial.println("End of level 1");
          CircuitPlayground.setPixelColor(2, 255, 255, 255);
          break;
```
for every other level, just replace the game_Difficulty = 1 with that level #.
This calls the Lighting Pattern function and then the User Input Function So let me explain those now:
---
##Lighting Pattern Function

The light pattern function is fairly straightforward, for the most part it just takes a random value, either 0 or 1, and uses that to assign 0 to left and 1 to right in order to 'truly' randomize which side the light pattern displays on. It repeats this until it reaches the value of the game difficulty, which sets how many patterns it plays in sequence, and then the function ends.

```
// plays a sequence of blue lights on the left side of the circuitplayground or red lights on the right side.
void game_Lights_Level() {
  delay(1000);
  Serial.println("Pattern starting");
  delay(50);
  CircuitPlayground.clearPixels();

  for (int i = 0; i < game_Difficulty; i++) {
    if (leftButton_intFlag || rightButton_intFlag) {
      Mode = 1;
      break;
    }
    rand_Number = random(0, 2);
    if (rand_Number == 0) {
      pattern_Side = "Left";
      rand_Int = 0;
      // Serial.println("Left lights"); (not for nromal gameplay, gives away pattern)
      CircuitPlayground.playTone(523.25, 80);
      for (int i = 0; i < 5; i++) {
        CircuitPlayground.setPixelColor(left_Leds[i], 0, 0, 255);
      }
      delay(500);
      CircuitPlayground.clearPixels();
      delay(500);
      game_Pattern_Int[light_Pattern_Stage] = rand_Int + 1;
      game_Pattern[light_Pattern_Stage] = pattern_Side;
      light_Pattern_Stage++;
    }
    if (rand_Number == 1) {
      pattern_Side = "Right";
      rand_Int = 1;
      // Serial.println("Right lights"); (not for normal gameplay, gives away pattern)
      CircuitPlayground.playTone(622.25, 80);
      for (int i = 0; i < 5; i++) {
        CircuitPlayground.setPixelColor(right_Leds[i], 255, 0, 0);
      }
      delay(500);
      CircuitPlayground.clearPixels();
      delay(500);
      game_Pattern_Int[light_Pattern_Stage] = rand_Int + 1;
      game_Pattern[light_Pattern_Stage] = pattern_Side;
      light_Pattern_Stage++;
    }
  }
  Serial.println();
  for (int i = 0; i < game_Difficulty; i++) {
    Serial.print(game_Pattern_Int[i]);
    Serial.print("\t \t");
  }
  Serial.println();
  Serial.println(" \n Pattern ended");
  // code to reset variables for next level
  light_Pattern_Stage = 0;
}  // end of light pattern
```
---
## User Input Function

What the user input function does is it takes the pattern the game made up in the light pattern function, and hides it from the player. The player is then tasked with pressing a button to correspond to the light pattern that was either on the left or right side of the board within 4 seconds. If the player does this job accurately, and quickly, they win the level, and move onto the next one. If they don't, then they lose and go back to level 1.

```
void game_User_Input_Level() {
  user_Matched_Pattern = 0;
  game_Matched_Pattern = 0;
  if (Mode == 0 && switch_intFlag) {
    light_Pattern_Stage = 0;
    game_Difficulty_Input = game_Difficulty;
    Serial.println("\n User input section starting");
    CircuitPlayground.clearPixels();
    for (int i = 0; i < game_Difficulty_Input; i++) {
      if (game_Pattern_Int[i] == 1)  // left side input code
      {
        for (int a = 150; a > 0; a--) {
          delay(2);
          for (int i = 0; i <= 9; i++) {
            CircuitPlayground.setPixelColor(leds[i], map(a, 0, 150, 0, 200), a, 0);
            if (leftButton_intFlag) {
              Serial.println("Left button pressed correctly");
              user_Pattern_Int[light_Pattern_Stage] = 1;
              game_Difficulty_Input++;
              delay_4s.repeat();
              // this light pattern is visual feedback to the user they pressed the button on time
              CircuitPlayground.playTone(523.25, 40);
              CircuitPlayground.setPixelColor(2, 0, 0, 255);
              CircuitPlayground.setPixelColor(1, 0, 0, 255);
              CircuitPlayground.setPixelColor(3, 0, 0, 255);
              delay(10);
              CircuitPlayground.setPixelColor(0, 0, 0, 155);
              CircuitPlayground.setPixelColor(4, 0, 0, 155);
              delay(80);
              CircuitPlayground.clearPixels();
              leftButton_intFlag = 0;
              left_Pressed = 1;
              break;
            }
            if (delay_4s.isExpired()) {
              Mode = 2;  // game was lost, try again
              Serial.println("4s timer ran out");
              delay(20);
              break;
            }
            if (rightButton_intFlag) {
              CircuitPlayground.playTone(622.25, 40);
              CircuitPlayground.setPixelColor(7, 255, 0, 0);
              CircuitPlayground.setPixelColor(8, 255, 0, 0);
              CircuitPlayground.setPixelColor(6, 255, 0, 0);
              delay(10);
              CircuitPlayground.setPixelColor(9, 155, 0, 0);
              CircuitPlayground.setPixelColor(5, 155, 0, 0);
              delay(80);
              CircuitPlayground.clearPixels();
              Mode = 2;
              rightButton_intFlag = 0;
              break;
            }
          }
          // allows the light pattern to be pressed and then immediately move on to the next one instead of waiting
          if (left_Pressed) {
            left_Pressed = false;
            break;
          }
        }
      }
      if (game_Pattern_Int[i] == 2)  // right side input code
      {
        for (int a = 150; a > 0; a--) {
          delay(2);
          for (int i = 0; i <= 9; i++) {
            CircuitPlayground.setPixelColor(leds[i], map(a, 0, 150, 0, 200), a, 0);
            if (rightButton_intFlag) {
              Serial.println("Right button pressed correctly");
              user_Pattern_Int[light_Pattern_Stage] = 2;
              game_Difficulty_Input++;
              delay_4s.repeat();
              // this light pattern is visual feedback to the user they pressed the button on time
              CircuitPlayground.playTone(622.25, 40);
              CircuitPlayground.setPixelColor(7, 255, 0, 0);
              CircuitPlayground.setPixelColor(8, 255, 0, 0);
              CircuitPlayground.setPixelColor(6, 255, 0, 0);
              delay(10);
              CircuitPlayground.setPixelColor(9, 155, 0, 0);
              CircuitPlayground.setPixelColor(5, 155, 0, 0);
              delay(80);
              CircuitPlayground.clearPixels();
              rightButton_intFlag = 0;
              right_Pressed = 1;
              break;
            }
            if (delay_4s.isExpired()) {
              Mode = 2;  // game was lost, try again
              Serial.println("4s timer ran out");
              break;
            }
            if (leftButton_intFlag) {
              CircuitPlayground.playTone(523.25, 40);
              CircuitPlayground.setPixelColor(2, 0, 0, 255);
              CircuitPlayground.setPixelColor(1, 0, 0, 255);
              CircuitPlayground.setPixelColor(3, 0, 0, 255);
              delay(10);
              CircuitPlayground.setPixelColor(0, 0, 0, 155);
              CircuitPlayground.setPixelColor(4, 0, 0, 155);
              delay(80);
              CircuitPlayground.clearPixels();
              Mode = 2;
              leftButton_intFlag = 0;
              break;
            }
          }
          // allows the light pattern to be pressed and then immediately move on to the next one instead of waiting
          if (right_Pressed) {
            right_Pressed = false;
            break;
          }
        }
      }
      light_Pattern_Stage++;
    }
    for (int i = 0; i < game_Difficulty; i++) {
      game_Matched_Pattern = game_Matched_Pattern + game_Pattern_Int[i];
    }
    for (int i = 0; i < game_Difficulty; i++) {
      if (user_Pattern_Int[i] == game_Pattern_Int[i]) {
        user_Matched_Pattern = user_Matched_Pattern + game_Pattern_Int[i];
      }
    }
    if (user_Matched_Pattern == game_Matched_Pattern && Mode == 0) {
      level_Win = 1;
    }
    for (int i = 0; i < game_Difficulty; i++) {
      Serial.print(user_Pattern_Int[i]);
      Serial.print("\t \t");
    }
  }
  Serial.println("\n"
                 "Light Pattern");
  for (int i = 0; i < game_Difficulty; i++) {
    Serial.print(game_Pattern[i] + "\t \t");
  }
  Serial.println();
  Serial.println();
  // Serial.println("End of user input section"); (for debugging)
}
```
---
## Level Win Function

The level win function is one of the most basic in this program, as all it does is show the user they did beat the level, and shows them which level they beat by displaying fading in and out green lights once for every level beaten. It also incriments the game difficulty and game level, which after this function the program will loop back around to the loading zone to await user input to start displaying the patterns again.
```
Serial.println("Congratulations! Here is your reward!");
  for (int a = 0; a < game_Difficulty; a++) {
    for (int i = 0; i < 9; i++) {
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 255, 0);
      i++;
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 255, 0);
      delay(50);
      CircuitPlayground.playTone(440, 60);
    }
    for (int i = 0; i < 9; i++) {
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 0, 0);
      i++;
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 0, 0);
      delay(30);
    }
  }
  game_Difficulty++;
  game_Level++;
  game_On = 0;
  level_Win = 0;
```
---
## Game Win function

All this function does is create a sparkly effect for the player to enjoy after beating this memory game
```
void game_Win_Lights() {
  Serial.println("YOU WON!");
  for (int i = 0; i <= 3; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], random(0, 70), random(0, 40), random(10, 30));
    delay(50);
    CircuitPlayground.playTone(440, 60);
  }
  delay(10);
  for (int i = 0; i <= 2; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], 0, 0, 0);
    delay(40);
  }
  delay(20);
  for (int i = 0; i <= 5; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], random(40, 170), random(20, 50), random(0, 10));
    delay(20);
  }
  delay(30);
  for (int i = 0; i <= 2; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], 0, 0, 0);
    delay(10);
  }
  delay(30);
  for (int i = 0; i <= 7; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], random(10, 250), random(50, 180), random(40, 240));
    delay(30);
  }
  delay(30);
  for (int i = 0; i <= 12; i++) {
    CircuitPlayground.setPixelColor(leds[random(0, 9)], 0, 0, 0);
    delay(10);
  }
}
```
---
## Error function

What this function does is it processes and tells the serial monitor which error or failure statement happened, the only one I currently use is Mode 2, which is when the user does enter the proper pattern that matches the games pattern. It flashes red to the user and resets them back to level 1.
```
void Mode_2_Unhappy_Pattern_Restart() {
  CircuitPlayground.clearPixels();
  Serial.println("You Failed to input the correct pattern. Go Back to Level 1.");
  for (int a = 0; a < 3; a++) {
    for (int i = 0; i < 9; i++) {
      CircuitPlayground.setPixelColor(ledstopdown[i], 255, 0, 0);
      i++;
      CircuitPlayground.setPixelColor(ledstopdown[i], 255, 0, 0);
      delay(50);
      CircuitPlayground.playTone(220, 60);
    }
    for (int i = 0; i < 9; i++) {
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 0, 0);
      i++;
      CircuitPlayground.setPixelColor(ledstopdown[i], 0, 0, 0);
      delay(30);
    }
  }
  Serial.println("\n \n You lost, try again! \n \n");
  for (int i = 0; i <= game_Difficulty; i++) {
    user_Pattern_Int[i] = 0;
    game_Pattern_Int[i] = 0;
  }
  light_Pattern_Stage = 0;
  Mode = 0;
  game_On = 0;
  game_Level = 0;
}
```


## A bit about myself:
I like cats
