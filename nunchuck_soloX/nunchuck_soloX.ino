#include <WiiChuck.h>
#include <Wire.h>
#include "Keyboard.h"
#include "Mouse.h"

//VARIABLES
int VALUE_MAX_Y;
int VALUE_MIN_Y;
int VALUE_MAX_X;
int VALUE_MIN_X;

int ACCEL_MAX_X;
int ACCEL_MIN_X;
int ACCEL_MAX_Y;
int ACCEL_MIN_Y;

int const MOUSE_VEL = 8;

Nunchuck nunchuck(SDA, SCL);

void setup() {

  Serial.begin(115200);

  Keyboard.begin();
  Mouse.begin();

  nunchuck.begin();

  if (nunchuck.getJoyX() > 500) {
    VALUE_MAX_Y = 680;
    VALUE_MIN_Y = 620;
    VALUE_MAX_X = 680;
    VALUE_MIN_X = 600;
  } else {
    VALUE_MAX_Y = 170;
    VALUE_MIN_Y = 50;
    VALUE_MAX_X = 170;
    VALUE_MIN_X = 50;
  }

  //--

  if (nunchuck.getAccelX() > 1100) {
    ACCEL_MAX_Y = 1600;
    ACCEL_MIN_Y = 1340;
    ACCEL_MAX_X = 1700;
    ACCEL_MIN_X = 1350;
  } else {
    ACCEL_MAX_Y = 520;
    ACCEL_MIN_Y = 380;
    ACCEL_MAX_X = 550;
    ACCEL_MIN_X = 400;
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
  if (valueX > VALUE_MAX_X) {
    Keyboard.press('d');
    Keyboard.release('a');
  } else if (valueX < VALUE_MIN_X) {
    Keyboard.press('a');
    Keyboard.release('d');
  } else {
    Keyboard.release('a');
    Keyboard.release('d');
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

  //ACCELERACIÓN X

  if (accelX > ACCEL_MAX_X) {
    Mouse.move(MOUSE_VEL, 0, 0);
  } else if (accelX < ACCEL_MIN_X) {
    Mouse.move(-MOUSE_VEL, 0, 0);
  } else {
    //no hago nada
  }

  /*//ACCELERACIÓN Y

  if (accelY > ACCEL_MAX_Y) {
    Mouse.move(0, MOUSE_VEL, 0);
  } else if (accelY < ACCEL_MIN_Y) {
    Mouse.move(0, -MOUSE_VEL, 0);
  } else {
    //no hago nada
  }*/

  delay(1);
}
