/*
Keye New RFID Starter Kit 
Project 38
Password lock
Edit By Keyes
*/
#include <Keypad.h>
#include <Stepper.h>
// Number of steps for the stepper motor
const int stepsPerRevolution = 2048;
// Stepper motor setup
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);
// Keypad layout setup
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
// Create Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// Preset password
const String password = "1234";
String inputPassword;
void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10); // Set the stepper motor speed
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == '#') {
      // End of input, verify password
      if (inputPassword == password) {
        Serial.println("Access Granted");
        myStepper.step(stepsPerRevolution); // Rotate motor
      } else {
        Serial.println("Access Denied");
      }
      inputPassword = ""; // Reset input
    } else if (key == '*') {
      inputPassword = ""; // Clear input
    } else {
      inputPassword += key; // Store input characters
    }
  }
}
