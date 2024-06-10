#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
#include <Wire.h>
#include <SPI.h>

const uint8_t spREADY_TO_START[]    PROGMEM ={0xAE,0x91,0x85,0xD3,0x32,0xB8,0xB5,0xC6,0x35,0x4E,0x09,0xCA,0x7E,0x6A,0xDF,0xB9,0xCC,0xB4,0xFB,0xA9,0xE2,0xD4,0x30,0xD5,0xEE,0xB7,0x5A,0x55,0xEA,0x5A,0x10,0x99,0xA5,0x55,0x31,0x1B,0x1B,0x4E,0xA6,0x55,0xE5,0xAE,0xCA,0xD2,0x9D,0x5A,0x55,0xA6,0x08,0x49,0x2D,0x8D,0xB5,0x6C,0x11,0xB0,0x54,0x9A,0x06,0x0C,0xB0,0x8C,0x45,0x29,0xBC,0x4A,0x53,0xCB,0x4E,0xA5,0xA9,0xC2,0x4C,0xD5,0xF2,0x1A,0xA0,0x03,0x35,0x05,0xFC,0xA9,0x6C,0x01,0x05,0xFC,0x1D,0x0C,0x10,0x80,0xA6,0xD2,0x4F,0x1E,0x43,0x44,0x86,0xB4,0xBD,0xC5,0xAD,0x4E,0xE5,0x8B,0x77,0x18,0x37,0x59,0x85,0x9F,0xE6,0xA5,0xBA,0x78,0x67,0x33,0x6D,0x91,0x9F,0x22,0x1D,0xE6,0xD0,0x45,0xDA,0x49,0x46,0xB8,0x2C,0x00,0x03,0x64,0x19,0xCA,0x80,0x26,0x9B,0x11,0xE0,0x12,0x33,0x00,0xC0,0x03,0x00,0x00};
const uint8_t spTRY_AGAIN[]         PROGMEM ={0x0E,0x28,0xA1,0xA2,0x02,0x0E,0x28,0x6D,0x6C,0xC4,0xB6,0xAB,0xA5,0x8B,0xDB,0x15,0xEB,0xEE,0x5E,0xCE,0x6B,0x4E,0xE2,0xED,0x84,0xB9,0x26,0xBE,0xD1,0x0D,0x57,0x10,0x8B,0x9B,0xEB,0x44,0xD9,0xC1,0x0E,0x57,0x1C,0x8B,0x99,0xDB,0x46,0x39,0x69,0x8E,0xA6,0xEE,0x35,0x7B,0x64,0x35,0x26,0xF2,0x44,0xA7,0x94,0xE7,0x24,0x60,0x1B,0x15,0x55,0xCE,0x45,0x66,0x35,0x3B,0x29,0x45,0xD1,0xCC,0x6E,0xE1,0x66,0x64,0xD5,0x39,0x53,0x74,0x9B,0x13,0xE7,0xE0,0xAC,0x55,0xB3,0x4F,0x5C,0x5D,0x98,0x45,0xCC,0xBE,0xD1,0x8D,0x6E,0x72,0xF3,0x5B,0xAD,0x36,0x46,0x4F,0x95,0x8C,0x32,0xFB,0xDE,0x87,0xDE,0x66,0x35,0xD7,0x70,0xE5,0x06,0x4F,0x53,0xCC,0xBC,0x95,0x1A,0xA4,0xD5,0x08,0x19,0xC7,0x0F};
const uint8_t spYOU_WIN[]           PROGMEM ={0x26,0x2B,0x82,0x54,0x76,0x4B,0xA7,0x76,0x04,0x14,0xB6,0xBA,0x5D,0xBA,0x9E,0x48,0x30,0xEA,0xD6,0x69,0x6A,0x73,0x01,0xF7,0xB7,0xA7,0x6A,0xAD,0x0C,0x0C,0xFB,0x8F,0x2C,0x5A,0x55,0x2D,0xFD,0x52,0x62,0x6E,0xBA,0x06,0xA5,0x59,0x8E,0x72,0x1C,0x13,0x97,0x31,0xF7,0x61,0x2C,0x4D,0x5B,0x6E,0x64,0x8E,0x19,0x66,0x3D,0x55,0x16,0x9E,0x56,0xD8,0xF5,0xD4,0x35,0xA6,0x6A,0xC8,0x9A,0xDB,0xDC,0xF6,0xB6,0xB7,0x4D,0x9D,0xB4,0x66,0xEE,0xDE,0xD8,0xB7,0xAA,0xA5,0xC1,0xC2,0xB2,0x22,0xAB,0x86,0x7A,0x2F,0x8D,0x91,0x2D,0x6A,0x94,0x23,0x3D,0xDB,0x8E,0xA8,0xB0,0xCB,0x4E,0x2B,0x39,0x0F,0x00,0x00};

const uint8_t spONE[]               PROGMEM ={0xA6,0xA5,0x36,0xDF,0x89,0xEC,0xA5,0x86,0xDB,0xF9,0x42,0x56,0x9A,0x2A,0xE1,0xFB,0x0B,0x38,0x7D,0x6F,0x46,0x63,0x7C,0x9D,0x62,0x25,0x9E,0xCD,0x28,0x5C,0xAC,0x32,0xEA,0x38,0xBB,0x1A,0x4D,0x88,0x56,0x2A,0x53,0x67,0x76,0x79,0x70,0x83,0xF3,0x94,0x6C,0xE9,0xD6,0x0C,0xCE,0x61,0x8A,0xB4,0x3B,0x36,0xCA,0x20,0x1A,0xDC,0xAD,0xCD,0x28,0x8D,0x78,0x7B,0x5B,0x26,0x93,0x10,0x6A,0x95,0x9E,0xDA,0x4C,0x25,0x85,0x9A,0x5A,0x9A,0x07};
const uint8_t spTWO[]               PROGMEM ={0x02,0xD8,0x51,0x3C,0x00,0xC7,0x7A,0x18,0x20,0x85,0xE2,0xE5,0x16,0x61,0x45,0x65,0xD9,0x6F,0xBC,0xE3,0x99,0xB4,0x34,0x51,0x6B,0x49,0xC9,0xDE,0xAB,0x56,0x3B,0x11,0xA9,0x2E,0xD9,0x73,0xEB,0x7A,0x69,0x2A,0xCD,0xB5,0x9B,0x1A,0x58,0x2A,0x73,0xF3,0xCD,0x6A,0x90,0x62,0x8A,0xD3,0xD3,0xAA,0x41,0xF1,0x4E,0x77,0x75,0xF2};
const uint8_t spTHREE[]             PROGMEM ={0x0C,0x08,0xCA,0x44,0x02,0x1A,0xB0,0x40,0xC8,0x4D,0x15,0x73,0xCB,0xB4,0x39,0x0F,0xB9,0xE9,0x14,0xE6,0xAD,0xBE,0xE4,0x7E,0x50,0x50,0xA9,0xDF,0x91,0xE5,0x25,0x05,0x21,0x79,0x47,0x5E,0x7A,0x18,0x09,0xBD,0x5F,0x45,0xCB,0xC1,0xA8,0xF6,0x76,0x56,0xAD,0x2D,0x41,0x98,0xB3,0xEF,0xD4,0x2E,0x0C,0x5E,0x89,0xE5,0x66,0x65,0x3F,0xB8,0xC1,0x6B,0xF2,0x9A,0x0E,0x63,0x46,0xAF,0x38,0xAB,0x53,0xCC,0x03};
const uint8_t spFOUR[]              PROGMEM ={0xC0,0x00,0x23,0x2D,0x24,0xA0,0x01,0x0B,0x58,0x20,0xC5,0xBC,0xF7,0x11,0x4C,0x9A,0x9A,0xA4,0x84,0xF6,0x39,0x85,0x6E,0x97,0x93,0x98,0x84,0x8C,0xF5,0x5E,0x45,0xCD,0xDE,0x2A,0x91,0x63,0xD2,0x58,0x7D,0x6B,0x55,0xB1,0xF2,0x26,0xED,0xA9,0xE7,0xDB,0xC2,0x4B,0xFC,0xBA,0x49,0x2E,0x89,0x55,0xF4,0xE3,0x66,0xB5,0x95,0xAB,0xCC,0xBB,0x9B,0xED,0x30,0xF6,0x11,0x35,0x76,0x7B,0x00,0x00};
const uint8_t spFIVE[]              PROGMEM ={0xC0,0x80,0xE8,0xCD,0x46,0xEE,0x9C,0x6F,0x31,0x66,0x39,0xB9,0xF3,0x35,0x45,0xD6,0xF4,0x64,0xDE,0x77,0x27,0x79,0xDD,0x93,0x7A,0xDF,0x1D,0x14,0x45,0x4E,0xE6,0x43,0x97,0x73,0x05,0x3D,0x45,0x08,0x5D,0xC5,0x15,0xE5,0x54,0x21,0x56,0x06,0x67,0x90,0x53,0xC7,0x54,0x15,0x14,0x75,0x4F,0x1B,0xAB,0x17,0x43,0x25,0x59,0x5D,0x6C,0x5E,0xAA,0x59,0x75,0xF4,0xA9,0x59,0x69,0xD5,0xD4,0xD1,0xC7,0x6A,0xA1,0x5E,0x53,0xDB,0x10,0x8B,0x86,0x46,0x5D,0x6D,0x43,0x28,0x1A,0x1A,0x35,0xB4,0xF4,0x2E,0x4B,0xA9,0x75,0x62,0x33,0x98,0xA2,0xC6,0x5A,0x09,0xD9,0x20,0x95,0x7B,0x99,0xBB,0x06,0x04,0x38,0x27,0x84,0x00,0xE5,0xD5,0x1F};
const uint8_t spSIX[]               PROGMEM ={0x06,0x98,0xB6,0xC4,0x01,0x2F,0x66,0x46,0x20,0x01,0xD3,0x96,0x18,0x40,0x04,0xAF,0x96,0xA4,0x60,0xA1,0x52,0x8B,0x6F,0xB2,0x92,0x58,0xC4,0xC5,0x67,0xC9,0x4E,0x46,0x95,0x9A,0xB8,0x44,0x2D,0x76,0x7D,0x48,0xD8,0x13,0x15,0x03,0x00,0x10,0x60,0xA2,0x8B,0x00,0x8E,0xAD,0x52,0xC0,0xCF,0x9E,0x1A,0x10,0xC0,0x8F,0xE6,0x0F,0x00,0x00};
const uint8_t spSEVEN[]             PROGMEM ={0x0C,0xF8,0xDE,0x4C,0x02,0x1A,0xD0,0x80,0x05,0x2C,0xB0,0x62,0x17,0x2D,0x43,0x2B,0xF1,0x4D,0x6E,0xB2,0xD3,0x92,0x19,0x1F,0x6E,0xEC,0x51,0x5C,0xE5,0xB9,0x5A,0x58,0x3A,0x76,0x95,0xF7,0x9E,0x1E,0x30,0xAF,0x77,0x65,0xB2,0x29,0x42,0x2C,0xA6,0xB8,0xD9,0x64,0xCD,0x90,0x8A,0xE5,0x66,0x13,0x38,0x8C,0xD3,0x9D,0x58,0xB4,0x17,0x1B,0x29,0xF7,0x62,0x31,0x5E,0xC5,0x24,0xD3,0x88,0xCD,0x79,0xD6,0x90,0x71,0xF7};
const uint8_t spEIGHT[]             PROGMEM ={0x2D,0x2F,0xC5,0x54,0xA3,0x63,0xB5,0xBC,0x54,0x55,0xCD,0x1E,0x32,0xB2,0x5A,0x85,0xB8,0xBA,0xCE,0xCE,0x66,0x36,0x8B,0x56,0xD5,0x22,0xC8,0x55,0x73,0x63,0x2F,0x07,0x00,0x00,0x02,0x44,0x6D,0xCA,0x01,0x04,0x18,0x21,0x86,0x81,0x07};
const uint8_t spNINE[]              PROGMEM ={0x80,0x52,0xAA,0x32,0x2B,0xDA,0xB6,0xA9,0xAC,0x95,0x69,0xCD,0x48,0xAE,0xB1,0x5E,0xC7,0xAD,0x4D,0xAE,0x3A,0xBA,0x0C,0x51,0xAA,0x72,0xAA,0xE0,0x3B,0x25,0xB0,0xCD,0xA9,0x6C,0x9C,0x34,0xCD,0x2A,0x2B,0x77,0x61,0xD2,0x2C,0xEB,0x8C,0xDC,0xFB,0x49,0xD2,0x29,0x32,0x0A,0x17,0xC7,0xCD,0x22,0xEA,0xA9,0x62,0xA8,0x70,0xC9,0x7A,0xA7,0x4D,0x39,0x33,0x58,0x9B,0x8E,0x2E,0x76,0x0D,0xD5,0xA8,0xD3,0xFA,0xD0,0x43,0xB4,0x35,0x76,0x19,0x52,0x96,0xD0,0xCC,0xC8,0x65,0x88,0x43,0x45,0x23,0xAA,0xBA,0x31,0x0C,0x23,0xCD,0x18,0xC3,0x46,0x19,0x25,0x52,0xB3,0xA6,0x1A,0xB4,0xE3,0x48,0xA9,0x88,0x66,0x14,0x56,0x3D,0x22,0x1B,0x86,0xD1,0x29,0x37,0xCA,0x8C,0x0B,0x00,0xF0};


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

/*    Initializes the CircuitPlayground, buttons, switches, lights and speaker. Reads state of switch for immediate standby
*     or loading zone once in the loop code. Sets button & Switch interrupts. Includes a quick loading bar because I wanted
*     to add a bit of a wait before starting.
*
*/
void setup() {
  // put your setup code here, to run once:
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
}

/* 3 loop main functions:
*       - loading zone. flashing green next to left/right buttons to continue
*       - gameplay. left leds flash blue, red leds flash red, user remembers and plays back the pattern
*       - standby mode. Used to check user stats and be safe from accidental gameplay inputs
*       also error code & failure functions, of which there are 1 currently:
*          - Mode 2. user input the wrong pattern and is punished by being sent back to level 1
*/
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
// interrupt that plays when left button is pressed
void leftButtonISR() {
  leftButton_intFlag = true;
}  // end of leftButtonISR
// interrupt to run if right button was pressed
void rightButtonISR() {
  rightButton_intFlag = true;
}  // end of rightButtonISR
// interrupt that plays when switch changes state
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

/* checks for a sequence of inputs from the left and right buttons that correspond to the pattern played
* works by reading state of left and right side pattern played
* then, in order from first shown to last shown (pattern stage 1 -> 4 for example)
* displays all the LEDs and then fades them out from 255-0 brightness
* when LEDs hit 0 brightness, input of button press will not result in game progression
* but if button is pressed corresponding to side before 0, game will progress to next light
* if all lights in pattern correctly pressed, level is passed
* there is also a 4 second timer, after which the level is failed and user sent back to level 1 if no input detected.
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
// plays a sequence of green lights to indicate player won the level
void game_Lights_Level_Won() {
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
}
// tells the player they beat the game and plays a continuous sparkly light show to congratulate them
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
// plays a sequence of bright white lights and prints to serial the player failed, returns player to level 1.
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