#include <WiiChuck.h>
#include <Wire.h>
#include "Keyboard.h"
#include "Mouse.h"

//VARIABLES
int VALUE_MAX_Y;
int VALUE_MIN_Y;
int VALUE_MAX_X;
int VALUE_MIN_X;

int ACCEL_MAX_Y;
int ACCEL_MIN_Y;
int ACCEL_MAX_X;
int ACCEL_MIN_X;

int CENTER_X;
int CENTER_Y;

int CENTER_ACCEL_Y;

int const MOUSE_VEL = 15;
int const MARGEN_Y = 20;

Nunchuck nunchuck(SDA, SCL);

void setup() {

  Serial.begin(115200);

  Keyboard.begin();
  Mouse.begin();

  nunchuck.begin();

  if (nunchuck.getJoyX() > 500) {
    VALUE_MAX_Y = 680;
    VALUE_MIN_Y = 620;
    VALUE_MAX_X = 737;
    VALUE_MIN_X = 540;
    CENTER_X = 639;
    CENTER_Y = 122;
  } else {
    VALUE_MAX_Y = 170;
    VALUE_MIN_Y = 50;
    VALUE_MAX_X = 255;
    VALUE_MIN_X = 50;
    CENTER_X = 127;
    CENTER_Y = 122;
  }

  if (nunchuck.getAccelX() > 1100) {
    ACCEL_MAX_Y = 1640;
    ACCEL_MIN_Y = 1370;
    ACCEL_MAX_X = 1700;
    ACCEL_MIN_X = 1350;

    CENTER_ACCEL_Y = 1490;
  } else {
    ACCEL_MAX_Y = 600;
    ACCEL_MIN_Y = 340;
    ACCEL_MAX_X = 550;
    ACCEL_MIN_X = 400;

    CENTER_ACCEL_Y = 480;
  }
}


void loop() {
  nunchuck.readData();   // Read inputs and update maps
  nunchuck.printInputs(Serial); // Print all inputs
  int valueX = nunchuck.getJoyX();
  int valueY = nunchuck.getJoyY();

  int accelX = nunchuck.getAccelX();
  int accelY = nunchuck.getAccelY();
  int accelZ = nunchuck.getAccelZ();

  bool buttonZ = nunchuck.checkButtonZ();
  bool buttonC = nunchuck.checkButtonC();

  Serial.print(" Raw value x: ");
  Serial.print(valueX);
  Serial.print(" y: ");
  Serial.print(valueY);
  Serial.print("\r\n ");

  Serial.print(" AccelX: ");
  Serial.print(accelX);
  Serial.print("\r\n ");
  Serial.print(" AccelY: ");
  Serial.print(accelY);
  Serial.print("\r\n ");
  Serial.print(" AccelZ: ");
  Serial.print(accelZ);
  Serial.print("\r\n ");

  //COMBINO CON MOUSE

  //SIMULO TECLADO

  //coordenada X
  if (valueX > CENTER_X) {
    Mouse.move(map(valueX, CENTER_X, VALUE_MAX_X, 0, MOUSE_VEL), 0, 0);
  } else {
    Mouse.move(map(valueX, CENTER_X, VALUE_MIN_X, 0, -MOUSE_VEL), 0, 0);
  }

  //COORDENADA Y - ALANTE&ATRAS
  if (valueY > VALUE_MAX_Y) {
    Keyboard.press('w');
    Keyboard.release('s');
  } else if (valueY < VALUE_MIN_Y) {
    Keyboard.press('s');
    Keyboard.release('w');
  } else {
    Keyboard.release('w');
    Keyboard.release('s');
  }

  //ACCELERACIÓN Y

  if (accelY > (CENTER_ACCEL_Y + MARGEN_Y)) {
    Mouse.move(0, map(accelY, CENTER_ACCEL_Y, ACCEL_MAX_Y, 0, MOUSE_VEL), 0);
  } else if (accelY < (CENTER_ACCEL_Y - MARGEN_Y)) {
    Mouse.move(0, map(accelY, CENTER_ACCEL_Y, ACCEL_MIN_Y, 0, -MOUSE_VEL), 0);
  } else {
    //no hago nada
  }

  if (buttonZ) {
    Mouse.press(MOUSE_LEFT);
  } else {
    Mouse.release(MOUSE_LEFT);
  }

  if (buttonC) {
    Keyboard.press(' ');
  } else {
    Keyboard.release(' ');
  }

  //delay(1);
}
