///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Total Acceleration
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

float X, Y, Z, totalAccel;

int statusleds_left[] = { 9, 8, 7, 6, 5 };
int statusleds_right[] = { 0, 1, 2, 3, 4 };
int accel_Count = 0;  // incriments every time Acceleration is greater than a set value
bool game_Win = 0;
AsyncDelay delay_10s;

///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);

  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  delay_10s.start(10000, AsyncDelay::MILLIS);
}

///////////////////////////////////////////////////////////////////////////////
void loop() {

  X = 0;
  Y = 0;
  Z = 0;
  for (int i = 0; i < 10; i++) {
    X += CircuitPlayground.motionX();
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }
  X /= 10;
  Y /= 10;
  Z /= 10;

  totalAccel = sqrt(X * X + Y * Y + Z * Z);

  Serial.println(totalAccel);

  if (totalAccel < 9.4) {
    totalAccel = 9.4;
  }
  if (totalAccel > 15) {
    accel_Count++;
    totalAccel = 15;
  }
  if (accel_Count > 18) {
    game_Win = 1;
    accel_Count = 0;
  }
  CircuitPlayground.clearPixels();

  for (int i = 0; i <= accel_Count / 2; i++) {
    CircuitPlayground.setPixelColor(i, sqrt(X * X), sqrt(Y * Y), sqrt(Z * Z));
  }
  if (delay_10s.isExpired()) {
    Serial.println("10s has passed");
    if (game_Win) {
      for (int i = 0; i <= 3; i++) {
        CircuitPlayground.setPixelColor(statusleds_left[i], 255, 255, 255);
        CircuitPlayground.setPixelColor(statusleds_right[i], 255, 255, 255);
        delay(200);
      }
      CircuitPlayground.clearPixels();
      delay(200);
      for (int i = 0; i <= 5; i++) {
        for (int i = 0; i <= 3; i++) {
          CircuitPlayground.setPixelColor(statusleds_left[i], 255, 255, 255);
          CircuitPlayground.setPixelColor(statusleds_right[i], 255, 255, 255);
        }
        delay(200);
        CircuitPlayground.clearPixels();
               delay(200);
      }
    }
    game_Win = 0;
    accel_Count = 0;
    delay_10s.repeat();
  }

  delay(100);
}