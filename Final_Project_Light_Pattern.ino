#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int error_Code = 0;  // user input/game error codes:
/*
*  Error Code 1; user presses button while game displaying pattern.
*              pattern will repeat after showing it is unhappy
*
*
*
*
*/

long rand_Number = 0;
int rand_Int = 0; // can't use ints for rand() so need to set this value to use in int arrays

bool game_Win = 0;
bool left_pressed = 0;
bool right_pressed = 0;

int game_Level = 0;
int game_Difficulty = 4;
int light_Pattern_Stage = 0;

int left_Leds[] = { 0, 1, 2, 3, 4 };
int right_Leds[] = { 5, 6, 7, 8, 9 };
int leds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int user_Pattern_Int[] = {0, 0, 0, 0};
String user_Pattern[4];
int game_Pattern_Int[] = {0, 0, 0, 0};
String game_Pattern[4];
String pattern_Side = "nothing";
int sequence_Stage = 0;

const int interruptPinLB = 4;      // left button interrupt pin
const int interruptPinRB = 5;      // right button interrupt pin
const int interruptPinSwitch = 7;  // switch interrupt pin

volatile int ModeControl = 0;  // tells the program which lightshow to play based on this value

volatile bool leftButton_intFlag = 0;   // flag for left button pressed
volatile bool rightButton_intFlag = 0;  // flag for right button pressed
volatile bool switch_intFlag = 0;       // flag for switch pressed

AsyncDelay delay_10s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;
  CircuitPlayground.begin();
  delay(1500);
  Serial.println("Booting Up");
  delay(1500);
  randomSeed(analogRead(0));
  CircuitPlayground.clearPixels();
  switch_intFlag = digitalRead(7);  // check switch state at startup
  delay_10s.start(10000, AsyncDelay::MILLIS);
  attachInterrupt(digitalPinToInterrupt(interruptPinRB), rightButtonISR, FALLING);  // check right button, if pressed run through rightButtonISR code once
  attachInterrupt(digitalPinToInterrupt(interruptPinLB), leftButtonISR, FALLING);   // check left button, if pressed run through rightButtonISR code once
  attachInterrupt(digitalPinToInterrupt(interruptPinSwitch), switchISR, CHANGE);    // check if switch has been moved, run through switchISR code once
  Serial.println("Game starting soon");
  delay(2000);
  Serial.println("Loading: 0%");
  delay(1000);
  Serial.println("Loading 25%");
  delay(1000);
  Serial.println("Loading 50%");
  delay(1000);
  Serial.println("Loading 75%");
  delay(1000);
  Serial.println("Loading 100%");
  delay(2000);
  Serial.println("Game ready");
  delay(1000);
  Serial.println("Ready? Press both buttons to continue."); // need to debounce the pressing of both buttons
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);

  switch (error_Code) {
    case 0:
      break;
    case 1:
      error_Code_1_Unhappy_Pattern_Interrupted();
  }


  if (leftButton_intFlag == 1 && rightButton_intFlag == 1 && game_Level == 0) {
    Serial.println("Level 1 Starting");
    light_Pattern_Stage = 0;
    game_Level = 1;
  }
  // displays when the left button has been pressed
  if (leftButton_intFlag) {
    Serial.println("Left Button pressed!");
    leftButton_intFlag = false;
  }

  if (rightButton_intFlag) {
    Serial.println("Right Button pressed!");
    rightButton_intFlag = false;
  }
  if (game_Level == 1 && light_Pattern_Stage < 4) {
    game_Difficulty = 4;
    game_Lights_Level();
  }
  /*
  if (delay_10s.isExpired()) {
    if (user_Pattern == game_Pattern) {
      //play "You won the level" audio
      level_Won();
      game_Level++;  //increase game level
                     // incriment game_level
    }
    if (user_Pattern != game_Pattern) {
      // play "try again" audio
      // play "try again" lightshow
      // restart game_level
    }
  }
  */
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
void level_Won() {
}

// plays a sequence of blue lights on the elft side of the circuitplayground or red lights on the right side.
void game_Lights_Level() {
  delay(1000);
  Serial.println("Pattern starting");
  delay(50);
  CircuitPlayground.clearPixels();

  for (int i = 0; i < 4; i++) {
    if (leftButton_intFlag || rightButton_intFlag) {
      error_Code = 1;
      break;
    }
    rand_Number = random(0, 2);
    if (rand_Number == 0) {
      pattern_Side = "Left";
      rand_Int = 0;
      Serial.println("Left lights");
      for (int i = 0; i < 5; i++) {
        CircuitPlayground.setPixelColor(left_Leds[i], 0, 0, 255);
      }
      delay(500);
      CircuitPlayground.clearPixels();
      delay(500);
      game_Pattern_Int[light_Pattern_Stage] = rand_Int;
      game_Pattern[light_Pattern_Stage] = pattern_Side;
      light_Pattern_Stage++;
    }
    if (rand_Number == 1) {
      pattern_Side = "Right";
      rand_Int = 1;
      Serial.println("Right lights");
      for (int i = 0; i < 5; i++) {
        CircuitPlayground.setPixelColor(right_Leds[i], 255, 0, 0);
      }
      delay(500);
      CircuitPlayground.clearPixels();
      delay(500);
      game_Pattern_Int[light_Pattern_Stage] = rand_Int;
      game_Pattern[light_Pattern_Stage] = pattern_Side;
      light_Pattern_Stage++;
    }
  }
  Serial.println();
  for (int i = 0; i < 4; i++) {
    Serial.print(game_Pattern[i] + "\t \t");
  }
  Serial.println();
  Serial.println();
  for (int i = 0; i < 4; i++) {
    Serial.print(game_Pattern_Int[i]);
    Serial.print("\t \t");
  }
  Serial.println();
  Serial.println(" \n Pattern ended");
}
void game_Lights_Level_Won() {
}
void game_UserInput_Level() {
  Serial.println("User input section starting");
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
  game_Level = 1;
}