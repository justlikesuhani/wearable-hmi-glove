/*
  =====================================================
  GESTURE-BASED WEARABLE GAMING GLOVE
  Hardware: Arduino Uno + MPU6050
  Controls: Tilt hand to send game controls
  
  Gesture Mapping:
    Tilt LEFT       → Left Arrow  (Subway Surfers: move left)
    Tilt RIGHT      → Right Arrow (Subway Surfers: move right)
    Tilt FORWARD    → Up Arrow    (Subway Surfers: jump)
    Tilt BACKWARD   → Down Arrow  (Subway Surfers: roll/duck)
  
  How it works:
    MPU6050 reads acceleration → converted to angles →
    Python script on PC reads Serial and presses actual keys
  =====================================================
*/

#include <Wire.h>

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

double x;
double y;
double Xdiff;
double Ydiff;

bool runningX = true;
bool runningY = true;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // Wake up MPU6050
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  // Read accelerometer data from MPU6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Convert raw values to angles
  int xAng = map(AcX, minVal, maxVal, -90, 90);
  int yAng = map(AcY, minVal, maxVal, -90, 90);
  int zAng = map(AcZ, minVal, maxVal, -90, 90);

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);

  Xdiff = (x < 180) ? x : (360 - x);
  Ydiff = (y < 160) ? (y + 20) : abs(340 - y);

  // Reset flags when hand returns to neutral position
  if (x < 5 || x > 355) runningX = true;
  if (y < 345 && y > 335) runningY = true;

  if (Xdiff > Ydiff) {
    // TILT FORWARD → JUMP (Up Arrow)
    if (x > 50 && x < 180 && runningX == true) {
      Serial.println("UP");
      runningX = false;
    }
    // TILT BACKWARD → DUCK/ROLL (Down Arrow)
    else if (x < 320 && x > 180 && runningX == true) {
      Serial.println("DOWN");
      runningX = false;
    }
  }
  else if (Xdiff < Ydiff) {
    // TILT LEFT → LEFT Arrow
    if (y > 10 && y < 160 && runningY == true) {
      Serial.println("LEFT");
      runningY = false;
    }
    // TILT RIGHT → RIGHT Arrow
    else if (y < 310 && y > 160 && runningY == true) {
      Serial.println("RIGHT");
      runningY = false;
    }
  }

  Xdiff = 0;
  Ydiff = 0;
  delay(50);
}
