#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int Mode = 0;  // user input/game error codes:
/*
*  Error Code 1; user presses button while game displaying pattern.
*              pattern will repeat after showing it is unhappy
*  Mode 2: user didn't press button fast enough
*             will restart at level 1
*
*
*/

long rand_Number = 0;
int rand_Int = 0;  // can't use ints for rand() so need to set this value to use in int arrays

bool game_On = 0;
bool game_Win = 0;
bool left_Pressed = 0;
bool right_Pressed = 0;
bool clear_Pixels = 0;

int level_Win = 0;
int game_Level = 0;
int game_Level_Save = 0;
int game_Difficulty = 2;
int game_Difficulty_Input = 0;
int light_Pattern_Stage = 0;
int restart = 0;
int user_Matched_Pattern = 0;
int game_Matched_Pattern = 0;

int left_Leds[] = { 0, 1, 2, 3, 4 };
int right_Leds[] = { 5, 6, 7, 8, 9 };
int leds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int ledsoffset[] = { 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 };
int ledstopdown[] = { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 };

int user_Pattern_Int[14];
String user_Pattern[14];
int game_Pattern_Int[14];
String game_Pattern[14];
String pattern_Side = "nothing";
int sequence_Stage = 0;

const int interruptPinLB = 4;      // left button interrupt pin
const int interruptPinRB = 5;      // right button interrupt pin
const int interruptPinSwitch = 7;  // switch interrupt pin

volatile int ModeControl = 0;  // tells the program which lightshow to play based on this value

volatile bool leftButton_intFlag = 0;   // flag for left button pressed
volatile bool rightButton_intFlag = 0;  // flag for right button pressed
volatile bool switch_intFlag = 0;       // flag for switch pressed

AsyncDelay delay_4s;
AsyncDelay delay_10s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
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
  delay(400);
  Serial.println("Ready? Press both buttons to continue.");  // need to debounce the pressing of both buttons
  switch_intFlag = digitalRead(7);                           // check switch state at startup
  CircuitPlayground.clearPixels();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (switch_intFlag) {

    if (clear_Pixels) {
      CircuitPlayground.clearPixels();
      clear_Pixels = 0;
    }
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

    if (leftButton_intFlag || rightButton_intFlag && !game_On) {
      // loading zone between game levels
      switch (game_Level) {
        case 0:
          delay(50);
          Serial.println("Level 1 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 1;
          game_On = 1;
          break;
        case 1:
          delay(50);
          Serial.println("Level 2 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 2;
          game_On = 1;
          break;
        case 2:
          delay(50);
          Serial.println("Level 3 Starting");
          delay(50);
          light_Pattern_Stage = 0;
          game_Level = 3;
          game_On = 1;
          break;
        case 3:

          break;
        case 4:

          break;
        case 5:

          break;
        case 6:

          break;
        case 7:

          break;
        case 8:

          break;
        case 9:

          break;
      }
    }
    // displays when the left button has been pressed
    if (leftButton_intFlag) {
      Serial.println("Left Button pressed!");
      CircuitPlayground.playTone(523.25, 40);
      CircuitPlayground.setPixelColor(2, 0, 0, 255);
      CircuitPlayground.setPixelColor(1, 0, 0, 255);
      CircuitPlayground.setPixelColor(3, 0, 0, 255);
      delay(40);
      CircuitPlayground.setPixelColor(0, 0, 0, 155);
      CircuitPlayground.setPixelColor(4, 0, 0, 155);
      delay(80);
      CircuitPlayground.clearPixels();
      leftButton_intFlag = false;
    }

    if (rightButton_intFlag) {
      Serial.println("Right Button pressed!");
      CircuitPlayground.playTone(622.25, 40);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      delay(40);
      CircuitPlayground.setPixelColor(9, 155, 0, 0);
      CircuitPlayground.setPixelColor(5, 155, 0, 0);
      delay(80);
      CircuitPlayground.clearPixels();
      CircuitPlayground.clearPixels();
      rightButton_intFlag = false;
    }

    // level 1 code: 4 lights left or right, user inputs same pattern to win
    if (game_Level == 1 && game_On) {
      game_Difficulty = 2;
      game_Lights_Level();  // plays light pattern 4 times
      CircuitPlayground.clearPixels();
      delay(500);
      delay_4s.start(4000, AsyncDelay::MILLIS);
      game_User_Input_Level();  // checks for 4 inputs from the user
      if (level_Win == 1) {
        Serial.println("USER WON THE LEVEL");
        game_Lights_Level_Won();  // plays won level happy light sequence and bumps up difficulty by 1
      } else if (level_Win == 0) {
        Mode = 2;
      } else {
        Mode = 2;
      }
      for (int i = 0; i <= game_Difficulty; i++) {
        user_Pattern_Int[i] = 0;
      }
      Serial.println("End of level 1");
      CircuitPlayground.setPixelColor(2, 255, 255, 255);
    }

    // level 2 code, 5 lights left or right, user inputs same pattern to win
    if (game_Level == 2 && game_On) {
      game_Difficulty = 3;
      Serial.println("Level 2 Start");
      game_Lights_Level();
      CircuitPlayground.clearPixels();
      delay(500);
      delay_4s.start(4000, AsyncDelay::MILLIS);
      game_User_Input_Level();
      if (level_Win == 1) {
        Serial.println("USER WON THE 2nd LEVEL");
        game_Lights_Level_Won();
      } else if (level_Win == 0) {
        Mode = 2;
      } else {
        Mode = 2;
      }
      for (int i = 0; i <= game_Difficulty; i++) {
        user_Pattern_Int[i] = 0;
      }
      Serial.println("End of level 2");
    }
    // level 3 codem, 6 lights left or right, user inputs same pattern to win
    if (game_Level == 3 && game_On) {
      game_Difficulty = 4;
      Serial.println("Level 3 Start");
      game_Lights_Level();
      CircuitPlayground.clearPixels();
      delay(500);
      delay_4s.start(4000, AsyncDelay::MILLIS);
      game_User_Input_Level();
      if (level_Win == 1) {
        Serial.println("USER WON THE 3rd LEVEL");
        game_Lights_Level_Won();
      } else if (level_Win == 0) {
        Mode = 2;
      } else {
        Mode = 2;
      }
      for (int i = 0; i <= game_Difficulty; i++) {
        user_Pattern_Int[i] = 0;
      }
      Serial.println("End of level 3");
    }

    // error codes and failure statements
    switch (Mode) {
      case 0:
        break;
      case 1:
        error_Code_1_Unhappy_Pattern_Interrupted();
        break;
      case 2:
        Mode_2_Unhappy_Pattern_Restart();
        break;
    }
  }

  // waiting mode
  if (!switch_intFlag) {
    clear_Pixels = 1;
    delay_10s.start(10000, AsyncDelay::MILLIS);
    if (delay_10s.isExpired()) {
      Serial.println("Game off. In Standby Mode");
      delay_10s.restart();
    }
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
      delay(40);
      CircuitPlayground.setPixelColor(0, 0, 0, 155);
      CircuitPlayground.setPixelColor(4, 0, 0, 155);
      delay(80);
      CircuitPlayground.clearPixels();
      leftButton_intFlag = false;
    }

    if (rightButton_intFlag) {
      Serial.println("Right Button pressed!");
      CircuitPlayground.playTone(622.25, 40);
      CircuitPlayground.setPixelColor(7, 255, 0, 0);
      CircuitPlayground.setPixelColor(8, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0);
      delay(40);
      CircuitPlayground.setPixelColor(9, 155, 0, 0);
      CircuitPlayground.setPixelColor(5, 155, 0, 0);
      delay(80);
      CircuitPlayground.clearPixels();
      CircuitPlayground.clearPixels();
      rightButton_intFlag = false;
    }
  }
}
void leftButtonISR() {
  leftButton_intFlag = true;
}  // end of leftButtonISR

// function to run if right button was pressed
void rightButtonISR() {
  rightButton_intFlag = true;
}  // end of rightButtonISR

void switchISR() {
  switch_intFlag = digitalRead(7);  // this allowed me to avoid debounce code
}  // end of switchISR

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
      Serial.println("Left lights");
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
      Serial.println("Right lights");
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
    Serial.print(game_Pattern[i] + "\t \t");
  }
  Serial.println();
  Serial.println();
  for (int i = 0; i < game_Difficulty; i++) {
    Serial.print(game_Pattern_Int[i]);
    Serial.print("\t \t");
  }
  Serial.println();
  Serial.println(" \n Pattern ended");
  // code to reset variables for next level
  light_Pattern_Stage = 0;
}

/* checks for a sequence of inputs from the left and right buttons that correspond to the pattern played
* works by reading state of left and right side pattern played
* then, in order from first shown to last shown (pattern stage 1 -> 4 for example)
* displays the LEDS on that side and then fades them out from 255-0 brightness
* when LEDs hit 0 brightness, input of button press will not result in game progression
* but if button press corresponding to side before 0, game will progress to next light
* if all lights in pattern correctly pressed, level is passed
*/
void game_User_Input_Level() {
  user_Matched_Pattern = 0;
  game_Matched_Pattern = 0;
  if (Mode == 0 && switch_intFlag) {
    light_Pattern_Stage = 0;
    game_Difficulty_Input = game_Difficulty;
    Serial.println("\n User input section starting");
    CircuitPlayground.clearPixels();
    for (int i = 0; i < game_Difficulty_Input; i++) {
      if (game_Pattern_Int[i] == 1)  // if left side
      {
        for (int a = 150; a > 0; a--) {
          delay(2);
          for (int i = 0; i <= 9; i++) {
            CircuitPlayground.setPixelColor(leds[i], map(a, 0, 150, 0, 255), a, 0);
            if (leftButton_intFlag) {
              Serial.println("Left button pressed correctly");
              user_Pattern_Int[light_Pattern_Stage] = 1;
              game_Difficulty_Input++;
              delay_4s.repeat();
              // this light pattern is visual feedback to the user they pressed the button on time
              CircuitPlayground.playTone(523.25, 80);
              CircuitPlayground.setPixelColor(2, 0, 0, 255);
              CircuitPlayground.setPixelColor(1, 0, 0, 255);
              CircuitPlayground.setPixelColor(3, 0, 0, 255);
              delay(40);
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
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 255, 255);
              }
              delay(400);
              CircuitPlayground.clearPixels();
              delay(400);
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 0, 0);
              }
              delay(400);
              CircuitPlayground.clearPixels();
              delay(400);
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 0, 0);
              }
              delay(400);

              Mode = 1;
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
      if (game_Pattern_Int[i] == 2)  // if right side
      {
        for (int a = 150; a > 0; a--) {
          delay(2);
          for (int i = 0; i <= 9; i++) {
            CircuitPlayground.setPixelColor(leds[i], map(a, 0, 150, 0, 255), a, 0);
            if (rightButton_intFlag) {
              Serial.println("Right button pressed correctly");
              user_Pattern_Int[light_Pattern_Stage] = 2;
              game_Difficulty_Input++;
              delay_4s.repeat();
              // this light pattern is visual feedback to the user they pressed the button on time
              CircuitPlayground.playTone(622.25, 80);
              CircuitPlayground.setPixelColor(7, 255, 0, 0);
              CircuitPlayground.setPixelColor(8, 255, 0, 0);
              CircuitPlayground.setPixelColor(6, 255, 0, 0);
              delay(40);
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
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 255, 255);
              }
              delay(400);
              CircuitPlayground.clearPixels();
              delay(400);
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 0, 0);
              }
              delay(400);
              CircuitPlayground.clearPixels();
              delay(400);
              for (int i = 0; i <= 9; i++) {
                CircuitPlayground.setPixelColor(leds[i], 255, 0, 0);
              }
              delay(400);

              Mode = 1;
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
  Serial.println("End of user input section");
}
void game_Lights_Level_Won() {
  Serial.println("Congratulations! Here is your reward!");
  for (int a = 0; a < 2; a++) {
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
}
void error_Code_1_Unhappy_Pattern_Interrupted() {
  CircuitPlayground.clearPixels();
  delay(500);
  for (int i = 0; i < 9; i++) {
    CircuitPlayground.setPixelColor(leds[i], 255, 0, 0);
  }
  delay(500);
  CircuitPlayground.clearPixels();
  delay(500);
  for (int i = 0; i < 9; i++) {
    CircuitPlayground.setPixelColor(leds[i], 200, 200, 200);
  }
  delay(500);
  CircuitPlayground.clearPixels();
  delay(500);
  for (int i = 0; i < 9; i++) {
    CircuitPlayground.setPixelColor(leds[i], 200, 200, 200);
  }
  Serial.println("Error Code 1; interrupted pattern while in progress.");
  delay(1000);
  Serial.println("Pattern will restart after a short delay");
  delay(1000);
  for (int i = 0; i <= game_Difficulty; i++) {
    user_Pattern_Int[i] = 0;
    game_Pattern_Int[i] = 0;
  }
  light_Pattern_Stage = 0;
  Mode = 0;
  game_On = 0;
  game_Level = 0;
}
void Mode_2_Unhappy_Pattern_Restart() {
  CircuitPlayground.clearPixels();
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